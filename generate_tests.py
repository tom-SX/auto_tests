from bs4 import BeautifulSoup
import json
import random
import string
import re

products = ['Merlin']
current_product = ''
current_description = ''
detectors_dict = {}
trackers_dict = {}
num_of_columns = 0
cpp_code = ''
threshold_map_cpp = ''
trackers_threshold_map_cpp = ''
test_videos = {
    'Merlin': [
        "/home/tom/Desktop/merlin_runner/test_videos/ground_RGB/Caesarea_1405_0003_W_CMOS_FOV83_rgb/%05d.png",
        "/home/tom/Desktop/merlin_runner/test_videos/ground_MWIR/Caesarea_1500_0007_T_VOx_FOV40_lwir/%05d.png"
    ],
    'Meerkat': [
        
    ]
}


def getTitleNames(html_titles):
    title_names = []
    for title in html_titles:
        title_name = title.get_text()
        if title_name.startswith('Stream'):
            title_name = title_name.split(' ')[1]
            title_names.append(title_name)
    return title_names

def getColumns(header, isPop = True):
    columns = []
    for item in header:
        try:
            item_text = item.get_text()
            if item_text != '\n':
                item_text = '_'.join(item_text.split(' '))
                columns.append(item_text)
        except:
            continue
    if isPop:
        columns.pop(1)
    return columns

def getData(html_data) -> list:
    global current_description
    
    data = []
    for element in html_data:
        sub_data = []
        for sub_element in element:
            try:
                text = sub_element.get_text()
                if text != '\n':
                    sub_data.append(text)
            except:
                continue
        sdk_name = sub_data.pop(1)
        if len(sub_data) < num_of_columns:
            sub_data.append(current_description)
        else:
            current_description = sub_data[-1]
        sub_dict = {
            sdk_name: sub_data
        }
        data.append(sub_dict)
    return data

def getSubData(data, object_param, idx):
    tmp_data = [d for d in data]
    sub_data = []
    for row_idx in range(idx, len(data)):
        sdk_name = list(data[row_idx].keys())[0]
        if sdk_name.startswith(object_param):    
            if 'AttributeGroups' in sdk_name or 'PerClassThresholds' in sdk_name: # TODO - Skipping AttributeGroups + PerClassThresholds
                idx += 1
                continue
            tmp_name = ".".join(sdk_name.split(".")[1:])
            tmp_data[row_idx][tmp_name] = tmp_data[row_idx].pop(sdk_name)
            param_name = sdk_name.split(".")[0]
            if '[' in param_name:
                start = param_name.index('[') + 1
                end = param_name.index(']')
                tmp_value = param_name[start:end]
                tmp_data[row_idx][f'{tmp_value}#{tmp_name}'] = tmp_data[row_idx].pop(tmp_name)
            sub_data.append(tmp_data[row_idx])
            idx += 1
        else:
            break
    return sub_data, idx

def handleArrayName(sdk_name):
    start = sdk_name.index('[') + 1
    end = sdk_name.index(']')
    tmp_value = sdk_name[start:end]
    tmp_name = sdk_name[:start - 1]
    return f'{tmp_value}@{tmp_name}'

def getTableDict(columns, data):
    table_dict = {}
    tmp_idx = 0
    for row_idx in range(len(data)):
        if row_idx < tmp_idx:
            continue
        sdk_name = list(data[row_idx].keys())[0]
        if 'ScoreThresholds' in sdk_name: # TODO - Skipping ScoreThresholds
            continue
        orig_name = sdk_name
        if '[' in sdk_name:
            sdk_name = handleArrayName(sdk_name)
        table_dict[sdk_name] = {}
        for i in range(num_of_columns):
            val = data[row_idx][orig_name][i]
            if val == '(Object)' or val == '(ObjectMap)' or val == '(ObjectVector)':
                sub_data, tmp_idx = getSubData(data, sdk_name, row_idx + 1)
                table_dict[sdk_name] = getTableDict(columns, sub_data)
                break
            elif val.isdigit() or ('-' in val and i != num_of_columns - 1):
                val = eval(val)
            elif all(num.isdigit() for num in val.split('.')):
                val = float(val)
            table_dict[sdk_name][columns[i]] = val
    return table_dict

def getEnumDict(enum_table):
    enum_dict = {}
    i = 0
    while i < len(enum_table):
        values_list = [td for td in enum_table[i] if td != '\n']
        enum_name = values_list[0].get_text()
        enum_list = []
        num_of_values = eval(values_list[0]['rowspan'])
        if num_of_values > 1:
            enum_list += [td.get_text() for td in values_list[1:] if td.get_text() != '\n']
            i += 1
            for j in range(num_of_values - 1):
                for item in enum_table[i]:
                    if item.get_text() != '\n':
                        enum_list.append(item.get_text())
                i += 1
        else:
            enum_list.append(values_list[1].get_text())
            i += 1
        enum_dict[enum_name] = enum_list
    return enum_dict

def getDetectorDict(detectors_table):
    global detectors_dict
    i = 0
    while i < len(detectors_table):
        values_list = [td for td in detectors_table[i] if td != '\n'] # Get all row values
        detector_name = values_list[0].get_text() # Get detector name
        num_of_values = eval(values_list[0]['rowspan']) # Get num of rows for detector
        group_list = [[td.get_text() for td in values_list[2:] if td.get_text() != '\n'][0]] # Get first group
        for j in range(1, num_of_values):
            values_list = [td for td in detectors_table[i + j] if td != '\n'] # Get all row values
            if len(values_list) >= 3:
                group_list += [[td.get_text() for td in values_list[2:] if td.get_text() != '\n'][0]] # Get other groups
        i += num_of_values
        detectors_dict[detector_name] = group_list

def create_enum_printing_files(enums_file_path, header_file_path, source_file_path):
    # Read enums from the JSON file
    with open(enums_file_path, 'r') as f:
        enums = json.load(f)

    # Generate PrintTo functions for each enum
    print_functions = []
    header_content = "#ifndef ENUM_PRINTING_H\n#define ENUM_PRINTING_H\n\n#include <ostream>\n"
    header_content += '#include "PipelineInterface.h"\n\n'
    header_content += 'using namespace sightx;\n\n'
    header_content += 'namespace sightx::sdk {\n\n'
    for enum_name, enum_values in enums.items():
        header_content += f"    void PrintTo(sdk::{enum_name} e, std::ostream* os);\n"
        
        function = f"   void PrintTo(sdk::{enum_name} e, std::ostream* os) {{\n    switch (e) {{\n"
        for value in enum_values:
            function += f"          case sdk::{enum_name}::{value}:\n            *os << \"{enum_name}::{value}\";\n            break;\n"
        function += "           default:\n            *os << \"UNKNOWN_ENUM_VALUE\";\n            break;\n"
        function += "       }\n}\n"
        print_functions.append(function)
    header_content += "\n}\n"
    header_content += "\n#endif // ENUM_PRINTING_H\n"
    source_content = '#include "PipelineInterface.h"\n#include <ostream>\n'
    source_content += f'#include "{header_file_path}"\n\n'
    source_content += 'using namespace sightx;\n\n'
    source_content += 'namespace sightx::sdk {\n\n'
    source_content += "\n".join(print_functions)
    source_content += "\n}\n"

    # Write to the header file
    with open(header_file_path, 'w') as f:
        f.write(header_content)

    # Write to the source file
    with open(source_file_path, 'w') as f:
        f.write(source_content)


def generate_random_value(param_type, min_value, max_value):
    if param_type == "uint32_t" or param_type == "int32_t":
        return random.randint(min_value, max_value)
    elif param_type == "float" or param_type == "double":
        return f'{round(random.uniform(float(min_value), float(max_value)), 2)}f'
    elif param_type == "bool":
        return random.choice(["true", "false"])
    elif param_type == "std::string":
        return '"' + ''.join(random.choices(string.ascii_letters + string.digits, k=10)) + '"'
    else:
        return None

def isUpdatable(parameters):
    if 'Updatable' in parameters.keys():
        return parameters['Updatable'] == 'Updatable'
    for key in parameters.keys():
        if type(parameters[key]) == dict and 'Updatable' in parameters[key].keys():
            if parameters[key]['Updatable'] == 'Updatable':
                return True
        else:
            updatable_field = isUpdatable(parameters[key])
            if updatable_field:
                return True   
    return False

def generate_test_code(module_name, param_name, param_details, getter, setter, indent, enums_data, inner_value='', array_idx=''):
    test_code = ""
    default_value = param_details.get('Default_value', '0')
    param_type = param_details["Type"]
    update_getter = 'pStream->getConfiguration()' + getter[getter.index('.'):]
    update_setter = 'pStream->getConfiguration()' + setter[setter.index('.'):]
    is_updatable = isUpdatable(param_details)
    
    if isinstance(param_type, dict):
        return test_code  # We handle nested objects separately

    if param_type in enums_data:
        default_value = f'sdk::{param_type}::{default_value}'
    min_value = param_details.get("Min_allowed_value", None)
    max_value = param_details.get("Max_allowed_value", None)
    
    if default_value == '':
        default_value = '""'
    elif param_type == 'std::string':
        default_value = f'"{default_value}"'
    elif param_type == 'float':
        default_value = f'{float(default_value)}f'
        min_value = f'{float(min_value)}f'
        max_value = f'{float(max_value)}f'
    
    array_idx = re.sub(r'[^a-zA-Z0-9]', '_', str(array_idx))
    inner_value = re.sub(r'[^a-zA-Z0-9]', '_', str(inner_value))
    param_name = f'{param_name}{array_idx}' if array_idx != '' else param_name
    param_name = f'{param_name}{inner_value}' if inner_value != '' else param_name
    sub_module = '_'.join(string.replace('()', '') for string in getter.split('.get')[1:-1])
    sub_module = re.sub(r'[^a-zA-Z0-9]', '_', sub_module)
    test_code += f'{indent}// Test for {param_name} in {module_name}\n'
    test_code += f'{indent}TEST_F({module_name}Test, {f"{sub_module}_" if sub_module else ""}{param_name}Default) {{\n'
    test_code += f'{indent}    EXPECT_EQ({getter}, {default_value});\n'
    test_code += f'{indent}}}\n\n'
    if is_updatable:
        test_code += f'{indent}TEST_F({module_name}Test, Update_{f"{sub_module}_" if sub_module else ""}{param_name}Default) {{\n'
        test_code += f'{indent}    if (!::testing::GTEST_FLAG(update_tests)) {{\n'
        test_code += f'{indent}        GTEST_SKIP();\n'
        test_code += f'{indent}    }}\n'
        test_code += f'{indent}    EXPECT_EQ({update_getter}, {default_value});\n'
        test_code += f'{indent}}}\n\n'
    
    if param_type in enums_data:
        enum_values = enums_data[param_type]
        test_code += f'{indent}// Test for {param_name} in {module_name} (enum)\n'
        test_code += f'{indent}TEST_F({module_name}Test, {f"{sub_module}_" if sub_module else ""}{param_name}Enum) {{\n'
        for enum_value in enum_values:
            if setter.endswith(')'):
                test_code += f'{indent}    {setter[:-1]}sdk::{param_type}::{enum_value});\n'
            else:
                test_code += f'{indent}    {setter}(sdk::{param_type}::{enum_value});\n'
            test_code += f'{indent}    EXPECT_EQ({getter}, sdk::{param_type}::{enum_value}) << testing::PrintToString(sdk::{param_type}::{enum_value});\n'
        test_code += f'{indent}}}\n\n'
        if is_updatable:
            test_code += f'{indent}TEST_F({module_name}Test, Update_{f"{sub_module}_" if sub_module else ""}{param_name}Enum) {{\n'
            test_code += f'{indent}    if (!::testing::GTEST_FLAG(update_tests)) {{\n'
            test_code += f'{indent}        GTEST_SKIP();\n'
            test_code += f'{indent}    }}\n'
            for enum_value in enum_values:
                if update_setter.endswith(')'):
                    test_code += f'{indent}    {update_setter[:-1]}sdk::{param_type}::{enum_value});\n'
                else:
                    test_code += f'{indent}    {update_setter}(sdk::{param_type}::{enum_value});\n'
                test_code += f'{indent}    pStream->update();\n'
                test_code += f'{indent}    EXPECT_EQ({update_getter}, sdk::{param_type}::{enum_value}) << testing::PrintToString(sdk::{param_type}::{enum_value});\n'
            test_code += f'{indent}}}\n\n'
    
    elif min_value and max_value:
        test_code += f'{indent}TEST_F({module_name}Test, {f"{sub_module}_" if sub_module else ""}{param_name}Range) {{\n'
        if setter.endswith(')'):
            test_code += f'{indent}    {setter[:-1]}{min_value});\n'    
        else:
            test_code += f'{indent}    {setter}({min_value});\n'
        test_code += f'{indent}    EXPECT_EQ({getter}, {min_value});\n'
        if setter.endswith(')'):
            test_code += f'{indent}    {setter[:-1]}{max_value});\n'    
        else:
            test_code += f'{indent}    {setter}({max_value});\n'
        test_code += f'{indent}    EXPECT_EQ({getter}, {max_value});\n'
        if setter.endswith(')'):
            test_code += f'{indent}    EXPECT_THROW({setter[:-1]}{min_value} - 1), std::exception);\n'
            test_code += f'{indent}    EXPECT_THROW({setter[:-1]}{max_value} + 1), std::exception);\n'
        else:
            test_code += f'{indent}    EXPECT_THROW({setter}({min_value} - 1), std::exception);\n'
            test_code += f'{indent}    EXPECT_THROW({setter}({max_value} + 1), std::exception);\n'
        test_code += f'{indent}}}\n\n'
        
        if is_updatable:
            test_code += f'{indent}TEST_F({module_name}Test, Update_{f"{sub_module}_" if sub_module else ""}{param_name}Range) {{\n'
            test_code += f'{indent}    if (!::testing::GTEST_FLAG(update_tests)) {{\n'
            test_code += f'{indent}        GTEST_SKIP();\n'
            test_code += f'{indent}    }}\n'
            if update_setter.endswith(')'):
                test_code += f'{indent}    {update_setter[:-1]}{min_value});\n'    
            else:
                test_code += f'{indent}    {update_setter}({min_value});\n'
            test_code += f'{indent}    pStream->update();\n'
            test_code += f'{indent}    EXPECT_EQ({update_getter}, {min_value});\n'
            if update_setter.endswith(')'):
                test_code += f'{indent}    {update_setter[:-1]}{max_value});\n'    
            else:
                test_code += f'{indent}    {update_setter}({max_value});\n'
            test_code += f'{indent}    pStream->update();\n'
            test_code += f'{indent}    EXPECT_EQ({update_getter}, {max_value});\n'
            # if update_setter.endswith(')'):
            #     test_code += f'{indent}    EXPECT_THROW({update_setter[:-1]}{min_value} - 1), std::exception);\n'
            #     test_code += f'{indent}    EXPECT_THROW({update_setter[:-1]}{max_value} + 1), std::exception);\n'
            # else:
            #     test_code += f'{indent}    EXPECT_THROW({update_setter}({min_value} - 1), std::exception);\n'
            #     test_code += f'{indent}    EXPECT_THROW({update_setter}({max_value} + 1), std::exception);\n'
            test_code += f'{indent}}}\n\n'

    else:
        min_value = 0 if not min_value else min_value
        max_value = 1000 if not max_value else max_value
        random_value = generate_random_value(param_type, min_value, max_value)
        if random_value is not None:
            test_code += f'{indent}TEST_F({module_name}Test, {f"{sub_module}_" if sub_module else ""}{param_name}Random) {{\n'
            if setter.endswith(')'):
                test_code += f'{indent}    {setter[:-1]}{random_value});\n'
            else:
                test_code += f'{indent}    {setter}({random_value});\n'
            test_code += f'{indent}    EXPECT_EQ({getter}, {random_value});\n'
            test_code += f'{indent}}}\n\n'
            if is_updatable:
                test_code += f'{indent}TEST_F({module_name}Test, Update_{f"{sub_module}_" if sub_module else ""}{param_name}Random) {{\n'
                test_code += f'{indent}    if (!::testing::GTEST_FLAG(update_tests)) {{\n'
                test_code += f'{indent}        GTEST_SKIP();\n'
                test_code += f'{indent}    }}\n'
                if update_setter.endswith(')'):
                    test_code += f'{indent}    {update_setter[:-1]}{random_value});\n'
                else:
                    test_code += f'{indent}    {update_setter}({random_value});\n'
                test_code += f'{indent}    pStream->update();\n'
                test_code += f'{indent}    EXPECT_EQ({update_getter}, {random_value});\n'
                test_code += f'{indent}}}\n\n'
    
    return test_code

def parse_params(module_name, params, getter_prefix="", setter_prefix="", indent="    ", enums_data=None):
    test_code = ""
    for param_name, param_details in params.items():
        inner_value = ''
        array_idx = ''
        if '@' in param_name:
            array_idx, param_name = param_name.split('@')
            array_idx = 0 if 'N/A' in array_idx else array_idx
        if '#' in param_name:
            inner_value, param_name = param_name.split('#')
            inner_value = 0 if 'N/A' in inner_value else inner_value
            if str(inner_value) not in getter_prefix:
                getter_prefix = getter_prefix[:getter_prefix.rindex('(') + 1] + f'{inner_value})'
            if str(inner_value) not in setter_prefix:
                setter_prefix = setter_prefix[:setter_prefix.rindex('(') + 1] + f'{inner_value})'
        if "Type" in param_details:
            getter = f"{getter_prefix}.get{param_name}({array_idx})"
            setter = f"{setter_prefix}.set{param_name}{f'({array_idx}, )' if array_idx != '' else ''}"
            test_code += generate_test_code(module_name, param_name, param_details, getter, setter, indent, enums_data, inner_value, array_idx)
        elif isinstance(param_details, dict):
            nested_getter_prefix = f"{getter_prefix}.get{param_name}({array_idx})"
            nested_setter_prefix = f"{setter_prefix}.get{param_name}({array_idx})"
            test_code += parse_params(module_name, param_details, nested_getter_prefix, nested_setter_prefix, indent, enums_data)
    return test_code

def generate_tests_from_json(json_data, enums_data, cpp_test_file, project_name, print_enums_file_name):
    global current_product, test_videos
    video_paths = 'std::map<sdk::FlowSwitcherFlowId, std::string> videos = {\n'
    relevant_flows = [flow for flow in enums_data["FlowSwitcherFlowId"] if flow != "Sot"]
    for idx, flowId in enumerate(relevant_flows):
        video_paths += f'   {{sdk::FlowSwitcherFlowId::{flowId}, \"{test_videos[current_product][idx]}\"}},\n'
    video_paths += '};\n\n'
    
    cpp_code = (
        '#include "gtest/gtest.h"\n'
        '#include "PipelineInterface.h"\n'
        '#include <map>\n'
        '#include <string>\n\n'
        f'#include "{project_name}_generated_tests.h"\n'
        f'#include "{print_enums_file_name}.h"\n'
        '#include "helper.h"\n'
        '#include "update_tests_flag.h"\n'
        '#include "general_tests.h"\n\n'
        'using namespace sightx;\n\n'
        'namespace generated_tests {\n\n'
        'std::shared_ptr<sdk::Pipeline> pPipeline;\n\n'
        'sdk::StartStreamConfiguration startConfiguration;\n'
        'sdk::StartStreamConfiguration tmpStartConfiguration;\n'
        'std::shared_ptr<sdk::Stream> pStream;\n'
        'UserData* data;\n\n'
        f'{video_paths}'
        'std::map<sdk::FlowSwitcherFlowId, sdk::PixelFormat> pixels = {\n'
        '    {sdk::FlowSwitcherFlowId::Rgb, sdk::PixelFormat::BGR8},\n'
        '    {sdk::FlowSwitcherFlowId::Mwir, sdk::PixelFormat::GRAY8}\n'
        '};\n\n'
        f'{threshold_map_cpp}'
        f'{trackers_threshold_map_cpp}'
        'void setPipeline(std::shared_ptr<sdk::Pipeline> new_pipeline) {\n'
        '    pPipeline = new_pipeline;\n'
        '    setVideoPaths(videos);\n'
        '    setPixelFormats(pixels);\n'
        '    setThresholdMap(tMap);\n'
        '    setTrackerThresholdMap(trackerMap);\n'
        '}\n\n'
        'void setUserData(UserData* new_data) {\n'
        '    data = new_data;\n'
        '}\n\n'
    )
    
    for module_name, parameters in json_data.items():
        if 'Source' in module_name:
            continue
        cpp_code += f'// Test suit for {module_name}\n'
        cpp_code += f'class {module_name}Test : public ::testing::Test {{\n'
        cpp_code += 'protected:\n'
        cpp_code += '    void SetUp() override {\n'
        cpp_code += '        startConfiguration = pPipeline->createStartStreamConfiguration();\n'
        if module_name == 'GcSource':
            cpp_code += '        startConfiguration.getGcSource().appendGcParameters();\n'
        elif 'Detector' in module_name:
            cpp_code += f'        startConfiguration.get{module_name}().appendAveragePixelValue(0);\n'
            cpp_code += f'        startConfiguration.get{module_name}().appendPixelValueStandardDeviation(0);\n\n'
        elif 'Reid' in module_name:
            cpp_code += f'        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().appendFilters(sdk::ImageFilter::Unspecified);\n'
        if isUpdatable(parameters):
            cpp_code += '        if (::testing::GTEST_FLAG(update_tests)) {\n'
            cpp_code += '            tmpStartConfiguration = startConfiguration;\n'
            cpp_code += '            tmpStartConfiguration.getRawSource(); // Touch Raw Source\n'
            cpp_code += '            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever\n'
            cpp_code += '            pStream = pPipeline->startStream(tmpStartConfiguration);\n'
            cpp_code += '            waitForStreamStarted(pStream, data);\n'
            cpp_code += '        }\n\n'
            cpp_code += '    }\n\n'
            cpp_code += '    void TearDown() override {\n'
            cpp_code += '        if (::testing::GTEST_FLAG(update_tests)) {\n'
            cpp_code += '            pStream.reset();\n'
            cpp_code += '            waitForStreamStopped(data);\n'
            cpp_code += '        }\n\n'
        cpp_code += '    }\n\n'
        cpp_code += '};\n\n'
        

        cpp_code += parse_params(module_name, parameters, f"startConfiguration.get{module_name}()", f"startConfiguration.get{module_name}()", enums_data=enums_data)

    cpp_code += '}\n\n'
    
    cpp_code += 'namespace general_tests {\n'
    cpp_code += '// Instantiate general tests\n'
    cpp_code += 'INSTANTIATE_TEST_SUITE_P(GeneralTests, VideoStreams,\n'
    cpp_code += f'  ::testing::Values(sdk::FlowSwitcherFlowId::{", sdk::FlowSwitcherFlowId::".join(relevant_flows)}));\n'
    cpp_code += '}\n'

    with open(cpp_test_file, 'w') as file:
        file.write(cpp_code)

def getThresholdMap(json_data):
    global detectors_dict
    for module_name, parameters in json_data.items():
        if module_name in detectors_dict.keys():
            for group in json_data[module_name]["Groups"]:
                if 'ScoreThreshold' in group:
                    group_name = group.split("#")[0].replace('"', '')
                    if group_name in detectors_dict[module_name]:
                        idx = detectors_dict[module_name].index(group_name)
                        detectors_dict[module_name][idx] = {group_name: json_data[module_name]["Groups"][group]["Default_value"]}
            detectors_dict[module_name] = {key: value for d in detectors_dict[module_name] for key, value in d.items()}
    code_text = 'std::map<std::string, std::map<std::string, float>> tMap {\n'
    for detector in detectors_dict.keys():
        code_text += f'    {{"{detector}", {{'
        code_text += ', '.join([f'{{"{group}", {detectors_dict[detector][group]}f}}' for group in detectors_dict[detector].keys()])
        code_text += '}},\n'
    code_text += '};\n'
    return code_text

def getTrackerThresholdMap():
    global trackers_dict
    code_text = 'std::map<std::string, float> trackerMap {\n'
    for tracker in trackers_dict.keys():
        code_text += f'    {{"{tracker}", {trackers_dict[tracker]}}},\n'
    code_text += '};\n'
    return code_text

def main():
    global products, current_product, num_of_columns, detectors_dict, threshold_map_cpp, trackers_dict, trackers_threshold_map_cpp
    for project_name in products:
        current_product = project_name
        path = f'/usr/local/{project_name}/doc/module_parameters.html'
        soup = BeautifulSoup(open(path), 'html.parser')
        html_tables = soup.find_all("table")
        html_titles = soup.find_all("h2")
        title_names = getTitleNames(html_titles)
        enum_table = [item for item in html_tables[0].find_all("tr")][1:]
        enum_dict = getEnumDict(enum_table)
        detectors_table = [item for item in html_tables[1].find_all("tr")][1:]
        getDetectorDict(detectors_table)
        html_tables = html_tables[len(html_tables) - len(title_names):]
        result_dict = {}

        for i in range(len(html_tables)):
            header = html_tables[i].find("tr")
            columns = getColumns(header)
            num_of_columns = len(columns)
            html_data = html_tables[i].find_all("tr")[1:]
            data = getData(html_data)
            table_dict = getTableDict(columns, data)
            result_dict[title_names[i]] = table_dict
            
            if 'Tracker' in title_names[i] and 'InitThreshold' in table_dict.keys():
                trackers_dict[title_names[i]] = table_dict['InitThreshold']['Default_value']

        threshold_map_cpp = getThresholdMap(result_dict)
        trackers_threshold_map_cpp = getTrackerThresholdMap()
        
        json_file = f'{project_name.lower()}_sdk.json'
        enums_file = f'{project_name.lower()}_enums.json'
        cpp_test_file = f'{project_name.lower()}_generated_tests.cpp'
        print_enums_file_name = f'{project_name.lower()}_print_enums'

        with open(json_file, 'w') as jsonFile:
            json.dump(result_dict, jsonFile)

        with open(enums_file, 'w') as enumsFile:
            json.dump(enum_dict, enumsFile)

        # with open(json_file, 'r') as file:
        #     json_data = json.load(file)

        # with open(enums_file, 'r') as file:
        #     enums_data = json.load(file)

        create_enum_printing_files(enums_file, f'{print_enums_file_name}.h', f'{print_enums_file_name}.cpp')
        generate_tests_from_json(result_dict, enum_dict, cpp_test_file, project_name.lower(), print_enums_file_name)

if __name__ == "__main__":
    main()
