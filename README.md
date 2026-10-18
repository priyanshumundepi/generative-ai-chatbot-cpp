# Generative AI Chatbot Using C++

A simple Generative AI chatbot built using C++, Google Colab, and the Gemini API.

## Project Overview
This project allows users to enter questions and receive AI-generated responses through the Gemini API. It demonstrates how a C++ application can communicate with a Generative AI service.

## Objectives
- Learn the basics of Generative AI.
- Connect a C++ program to an AI API.
- Accept user questions and display AI-generated answers.
- Practice API integration and JSON response handling.

## Technologies Used
- C++
- Google Colab
- Google Gemini API
- libcurl
- nlohmann/json

## How It Works
1. The user enters a question.
2. The C++ program sends the question to the Gemini API.
3. The API generates a response.
4. The program displays the response.

## Setup and Execution
Install the required dependencies and compile the program:

```bash
g++ chatbot.cpp -o chatbot -lcurl
./chatbot
```

Set the `GEMINI_API_KEY` environment variable before running the program. Never write your API key directly in the source code or upload it to GitHub.

## Sample Output
The chatbot accepts a question and displays an AI-generated response. Add a screenshot of your actual output here when available.

## Learning Outcomes
- Understanding Generative AI and API integration
- Using C++ with HTTP requests
- Handling JSON responses
- Compiling and running C++ programs

## Conclusion
This project demonstrates a basic Generative AI chatbot using C++ and the Gemini API. It can be extended with conversation history, a graphical interface, and additional features.

## Author
**Priyanshu Mundepi**  
B.Tech CSE — First Year
