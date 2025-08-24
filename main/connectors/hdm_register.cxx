#include "hdm_register.hxx"

struct Buffer {
    std::string data;
    static size_t write(void* ptr, size_t size, size_t nmemb, void* userdata) {
        auto* buf = static_cast<Buffer*>(userdata);
        buf->data.append(static_cast<char*>(ptr), size * nmemb);
        return size * nmemb;
    }
};

void HdmRegCenConnector::connect()
{
    registerWithUrl(HdmEurekaConfig::EUREKA_HOST, HdmEurekaConfig::EUREKA_PORT);
}

void HdmRegCenConnector::registerWithUrl(const std::string& url, const short& port)
{
    const std::string eureka_url = std::string("http://")
         .append(url).append(1, ':')
         .append(std::to_string(port))
         .append("/eureka/apps/")
         .append(HdmAppConfig::APP_NAME);

    const std::string body = R"({
  "instance": {
    "instanceId": ")" + HdmAppConfig::APP_NAME + ":" + std::to_string(8080) + R"(",
    "hostName": ")" + HdmAppConfig::APP_NAME + R"(",
    "app": ")" + HdmAppConfig::APP_NAME + R"(",
    "ipAddr": ")" + HdmAppConfig::APP_NAME + R"(",
    "status": "UP",
    "port": { "$": )" + std::to_string(8080) + R"(, "@enabled": true },
    "healthCheckUrl": ")" + HdmAppConfig::APP_NAME + ':' + std::to_string(8080) + R"(/health",
    "homePageUrl": ")" + HdmAppConfig::APP_NAME + ':' + std::to_string(8080) + R"(/info",
    "dataCenterInfo": { "@class": "com.netflix.appinfo.InstanceInfo$DefaultDataCenterInfo", "name": "MyOwn" }
  }
})";
    std::cout << eureka_url << std::endl;
    std::cout << body << std::endl;

    if (perform("POST", eureka_url, body))
    {
        std::cout << "register success!" << std::endl;
    }
    else
    {
        std::cerr << "register failed!" << std::endl;
    }

    registerCenterUrl_.clear();
    registerCenterUrl_ = std::move(eureka_url);
}

bool HdmRegCenConnector::perform(
    const std::string& method,
    const std::string& url,
    const std::string& body) const
{
    (void) method;
    CURL *curl = curl_easy_init();
    if (curl) {
        Buffer buf;
        curl_easy_reset(curl);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        struct curl_slist* hdrs = nullptr;
        hdrs = curl_slist_append(hdrs, "Content-Type: application/json");
        hdrs = curl_slist_append(hdrs, "Accept: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hdrs);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Buffer::write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);

        CURLcode res = curl_easy_perform(curl);

        delete hdrs;
        hdrs = nullptr;
        if (res != CURLE_OK) {
            std::cerr << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }
        long code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        std::cerr << curl_easy_strerror(res) << std::endl;
        std::cout << "code: " << code << std::endl;
        return (code >= 200 && code < 300);
    }
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return true;
}
