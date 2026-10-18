#include <iostream>
#include <cstdlib>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

size_t writeCallback(void* contents, size_t size,
                     size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    const char* key = getenv("GEMINI_API_KEY");

    if (key == nullptr || string(key).empty()) {
        cout << "API key not found. Please set it again." << endl;
        return 1;
    }

    string question;
    cout << "=== Generative AI Chatbot ===" << endl;
    cout << "Enter your question: ";
    getline(cin, question);

    CURL* curl = curl_easy_init();

    if (!curl) {
        cout << "Could not initialize connection." << endl;
        return 1;
    }

    string response;
    string url =
        "https://generativelanguage.googleapis.com/v1beta/"
        "models/gemini-3.8-flash:generateContent";

    json request = {
        {"contents", json::array({
            {{"parts", json::array({
                {{"text", question}}
            })}}
        })}
    };

    string body = request.dump();
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(
        headers, "Content-Type: application/json");
    string auth = string("x-goog-api-key: ") + key;
    headers = curl_slist_append(headers, auth.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);
    long status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

    if (result != CURLE_OK) {
        cout << "Connection error: "
             << curl_easy_strerror(result) << endl;
    } else {
        try {
            json data = json::parse(response);

            if (status == 200 &&
                data.contains("candidates") &&
                !data["candidates"].empty()) {
                cout << "\nAI: "
                     << data["candidates"][0]["content"]
                                  ["parts"][0]["text"]
                                  .get<string>()
                     << endl;
            } else {
                cout << "API error (HTTP " << status << ")." << endl;
                if (data.contains("error"))
                    cout << data["error"]["message"] << endl;
                else
                    cout << response << endl;
            }
        } catch (...) {
            cout << "Could not read the response. HTTP "
                 << status << endl;
        }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return 0;
}
