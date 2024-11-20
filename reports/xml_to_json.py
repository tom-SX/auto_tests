import xml.etree.ElementTree as ET
import json

# Load the XML file
xml_file_path = '../build/test_results.xml'  # Replace with the correct path to your file

# Parse the XML file
tree = ET.parse(xml_file_path)
root = tree.getroot()

# Jira-specific fields (you can modify or map them based on your Jira instance)
test_case_key_prefix = "TEST-"  # The prefix for your Jira test case keys (e.g., TEST-123)

# Function to convert XML test case to JSON format for Jira test case creation
def convert_test_case_to_json(test_case, test_case_key):
    result = test_case.get('result')
    status = "PASS" if result == "completed" else "FAIL" if result == "failed" else "SKIPPED"
    failure_message = ""
    
    # If the test case has a failure or skipped message, get it
    if test_case.find('failure') is not None:
        failure_message = test_case.find('failure').text
    elif test_case.find('skipped') is not None:
        failure_message = test_case.find('skipped').get('message')

    # Create the test case structure including the Jira Test Key and test type
    return {
        "fields": {
            "project": {
                "key": "TEST"  # Replace with your Jira project key
            },
            "summary": test_case.get('name'),  # The name of the test case
            "issuetype": {
                "name": "Test"  # Specify that this is a "Test" issue type in Jira
            },
            "description": failure_message or "No failure message",  # Test description
            "labels": ["automated-test"],  # Optionally add a label to categorize tests
            "testType": "Automated",  # Assuming automated tests; change if necessary
        }
    }

# Function to convert the entire XML report to JSON for test case creation
def convert_report_to_json(root):
    json_report = []

    # Iterate over each test suite in the XML
    for testsuite in root.findall('testsuite'):
        test_suite_data = {
            "testSuiteName": testsuite.get('name'),
            "testCases": []  # Initialize a list for the test cases
        }

        # Iterate over each test case within the current test suite
        for testcase in testsuite.findall('testcase'):
            # Generate the test case JSON and add it to the test cases list
            test_case_json = convert_test_case_to_json(testcase, testsuite.get('name'))
            test_suite_data["testCases"].append(test_case_json)

        # Add the test suite data to the report (now without failures, skipped, and time)
        json_report.append(test_suite_data)

    return json_report

# Convert the XML to JSON for test cases with test suite structure
json_data = convert_report_to_json(root)

# Save the JSON data to a file
output_file_path = 'test_cases.json'  # Specify the output path
with open(output_file_path, 'w') as json_file:
    json.dump(json_data, json_file, indent=4)

print(f"Converted XML to JSON with test suite structure and saved to {output_file_path}")
