#include "HttpRequest.h"

#include <sstream>

namespace nreq {

    HttpRequest::HttpRequest()
    {
    }

    std::future<std::string> HttpRequest::request(std::list<curlpp::OptionBase*> &optionList)
    {
        return std::async(
            std::launch::async,
            [](const std::list<curlpp::OptionBase*> &optionList) mutable {
                curlpp::Cleanup cleanup;
                curlpp::Easy req;
                
                for (auto option : optionList)
                {
                    req.setOpt(option);
                }

                std::ostringstream res;
                req.setOpt(new curlpp::options::WriteStream(&res));

                req.perform();

                return std::string(res.str());
            },
            optionList
        );
    }

    std::future<std::string> HttpRequest::get(const std::string &url, std::list<std::string> header)
    {
        std::list<curlpp::OptionBase*> optionList;
        optionList.push_back(new curlpp::options::Url(url));
        optionList.push_back(new curlpp::options::HttpHeader(header));

        return request(optionList);
    }

    std::future<std::string> HttpRequest::post(const std::string &url, const std::string &body, std::list<std::string> header)
    {
        header.push_back("Content-Type: application/json");

        std::list<curlpp::OptionBase*> optionList;
        optionList.push_back(new curlpp::options::Url(url));
        optionList.push_back(new curlpp::options::HttpHeader(header));
        optionList.push_back(new curlpp::options::PostFields(body));
        optionList.push_back(new curlpp::options::PostFieldSize(body.length()));

        return request(optionList);
    }

}