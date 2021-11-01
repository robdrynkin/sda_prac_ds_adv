#include "models/banner.h"
#include "models/hit.h"
#include "service/service.h"
#include "service/server.h"

int main(int argc, char* argv[]) {
    assert(argc == 4);
    std::string host(argv[1]);
    int port = atoi(argv[2]);
    std::string path(argv[3]);

    auto server = NServer::TServer(
        NService::CreateService(
            NModels::CreateDummyBannerModel(path + "/banner"),
            NModels::CreateDummyHitModel(path + "/hit")
        )
    );
    server.Run(host, port);
    return 0;
}
