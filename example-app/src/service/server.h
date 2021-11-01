#include <nlohmann/json.hpp>
#include "../../http/httplib.h"

#include "service.h"

using json = nlohmann::json;

namespace {
    std::string MakeResponse(const std::string& status, const json& data) {
        auto res = json({{"status", status}});
        res["data"] = data;
        return res.dump();
    }
}

namespace NServer {
    class TServer {
    public:
        TServer(NService::IServicePtr service): Service(service) {

            Server.Post("/update_vectors", [this](const httplib::Request& request, httplib::Response& response) {
                UpdateVectors(request, response);
            });

            Server.Post("/get_banners", [this](const httplib::Request& request, httplib::Response& response) {
                GetBanners(request, response);
            });

            Server.Post("/reset", [this](const httplib::Request& request, httplib::Response& response) {
                Reset(request, response);
            });
        }

    void UpdateVectors(const httplib::Request& request, httplib::Response& response) {
        auto args = json::parse(request.body);

        auto bannerIds = args["banner_ids"].get<std::vector<uint64_t>>();
        auto bannerFeatures = args["banner_features"].get<std::unordered_map<std::string, std::vector<std::vector<float>>>>();

        Service->UpdateVectors(bannerIds, bannerFeatures);
        response.set_content(MakeResponse("success", ""), "json");
    }

    void GetBanners(const httplib::Request& request, httplib::Response& response) {
        auto args = json::parse(request.body);
        auto hitFeatures = args["hit_features"].get<std::unordered_map<std::string, std::vector<float>>>();
        auto topK = args["top_k"].get<uint32_t>();

        NModels::TFeatures batchHitFeatures;
        for (const auto& [name, vec]: hitFeatures) {
            batchHitFeatures[name] = {vec};
        }

        auto bannerIds = Service->GetBanners(batchHitFeatures, topK);
        response.set_content(MakeResponse("success", bannerIds), "json");
    }

    void Reset(const httplib::Request& request, httplib::Response& response) {
        Service->Reset();
        response.set_content(MakeResponse("success", ""), "json");
    }

    void Run(const std::string& host, int port) {
        Server.listen(host.c_str(), port);
    }

    private:
        NService::IServicePtr Service;
        httplib::Server Server;
    };
}