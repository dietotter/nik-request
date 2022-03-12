#pragma once

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <future>
#include <list>
#include <memory>
#include <string>

namespace nreq {

    class HttpRequest
    {
    public:
        HttpRequest();

        std::future<std::string> request(std::list<curlpp::OptionBase*> &optionList);
        std::future<std::string> get(const std::string &url, std::list<std::string> header = std::list<std::string>());
        /**
         * body is using type application/json
         */
        std::future<std::string> post(const std::string &url, const std::string &body = "", std::list<std::string> header = std::list<std::string>());
    };

}