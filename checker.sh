#!/bin/bash

echo "Running memory tests..."
valgrind --leak-check=full --show-leak-kinds=all ./program
