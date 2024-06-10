#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <project_name>"
  exit 1
fi

PROJECT_NAME=$1
PROJECT_DIR="./plugins/${PROJECT_NAME}"

if [ -d "$PROJECT_DIR" ]; then
  echo "Plugin ${PROJECT_NAME} already exists."
  exit 1
fi

mkdir -p "$PROJECT_DIR"

# Create the new CMakeLists.txt
CMAKE_INPUT_FILE="./plugins/CMakeTemplate.txt"  
CMAKE_OUTPUT_FILE="${PROJECT_DIR}/CMakeLists.txt"
sed "s/PROJECT_NAME/${PROJECT_NAME}/g" "$CMAKE_INPUT_FILE" > "$CMAKE_OUTPUT_FILE"

# Append subdir to ./plugins/CMakeLists.txt
echo "add_subdirectory(${PROJECT_NAME})" >> ./plugins/CMakeLists.txt

# Add the template to the directory
TEMPLATE_INPUT_FILE="./plugins/template.cpp"  
TEMPLATE_OUTPUT_FILE="${PROJECT_DIR}/${PROJECT_NAME}.cpp"
sed "s/PROJECT_NAME/${PROJECT_NAME}/g" "$TEMPLATE_INPUT_FILE" > "$TEMPLATE_OUTPUT_FILE"

echo "Created new plugin: ${PROJECT_NAME}"
