#include "hdm_register.hxx"

struct Buffer {
    std::string data;
    static size_t write(void* ptr, size_t size, size_t nmemb, void* userdata) {
        auto* buf = static_cast<Buffer*>(userdata);
        buf->data.append(static_cast<char*>(ptr), size * nmemb);
        return size * nmemb;
    }
};

HdmRegCenConnector::HdmRegCenConnector() :
    registerUrl_("http://" + HdmEurekaConfig::EUREKA_HOST + ":" +
        std::to_string(HdmEurekaConfig::EUREKA_PORT) +
        "/eureka/apps/" +
        HdmAppConfig::APP_NAME),
    registerAppUrl_(registerUrl_ + "/" +
        HdmAppConfig::APP_NAME + ":" +
        std::to_string(HdmAppConfig::APP_PORT)),
    curl_(nullptr)
{
    curl_ = curl_easy_init();
}

HdmRegCenConnector::~HdmRegCenConnector()
{
    curl_easy_cleanup(curl_);
    curl_global_cleanup();
}

void HdmRegCenConnector::Register() const
{
    const std::string body = R"({
  "instance": {
    "instanceId": ")" + HdmAppConfig::APP_NAME + ":" + std::to_string(HdmAppConfig::APP_PORT) + R"(",
    "hostName": ")" + HdmAppConfig::APP_NAME + R"(",
    "app": ")" + HdmAppConfig::APP_NAME + R"(",
    "ipAddr": ")" + HdmAppConfig::APP_NAME + R"(",
    "status": "UP",
    "port": { "$": )" + std::to_string(HdmAppConfig::APP_PORT) + R"(, "@enabled": true },
    "healthCheckUrl": ")" + HdmAppConfig::APP_NAME + ':' + std::to_string(HdmAppConfig::APP_PORT) + R"(/health",
    "homePageUrl": ")" + HdmAppConfig::APP_NAME + ':' + std::to_string(HdmAppConfig::APP_PORT) + R"(/info",
    "dataCenterInfo": { "@class": "com.netflix.appinfo.InstanceInfo$DefaultDataCenterInfo", "name": "MyOwn" }
  }
})";

    if (performRegister(registerUrl_, body))
    {
        std::cout << "register success!" << std::endl;
    }
    else
    {
        std::cerr << "register failed!" << std::endl;
    }
}

bool HdmRegCenConnector::performRegister(
    const std::string& url,
    const std::string& body) const
{
    // [Q] To do check curl_ is nullptr?

    curl_easy_reset(curl_);
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "POST");

    struct curl_slist* hdrs = nullptr;
    hdrs = curl_slist_append(hdrs, "Content-Type: application/json");
    hdrs = curl_slist_append(hdrs, "Accept: application/json");
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, hdrs);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, body.c_str());

    // call back function to write response to a buffer
    Buffer buf;
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, Buffer::write);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &buf);

    CURLcode res = curl_easy_perform(curl_);
    curl_slist_free_all(hdrs);

    // do request
    if (res != CURLE_OK) {
        std::cerr << curl_easy_strerror(res) << std::endl;
        return false;
    }

    long code;
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &code);
    std::cerr << curl_easy_strerror(res) << std::endl;
    std::cout << "code: " << code << std::endl;

    return (code >= 200 && code < 300);
}

void HdmRegCenConnector::heartbeat() const
{

}

void HdmRegCenConnector::unregister() const
{
    // [Q] To do check curl_ is nullptr?

    curl_easy_reset(curl_);
    curl_easy_setopt(curl_, CURLOPT_URL, registerAppUrl_.c_str());
    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");

    // call back function to write response to a buffer
    Buffer buf;
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, Buffer::write);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &buf);

    // do request
    long httpCode = 0;
    CURLcode res = curl_easy_perform(curl_);
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &httpCode);

    if (res == CURLE_OK && (httpCode == 200 || httpCode == 204))
    {
        std::cout << "unregister success!" << std::endl;
    }
    else
    {
        std::cerr << "res: " << res << std::endl;
        std::cerr << "http code: " << httpCode << std::endl;
        std::cerr << "err message: " << buf.data << std::endl;
        std::cerr << "unregister failed!" << std::endl;
    }
}
