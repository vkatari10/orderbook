#include <iostream>

#include <matching-engine/matching_engine.hpp>


#define NL "\n" 
using std::cout;

#include <gateway/gateway.hpp>
#include "quickfix/SocketAcceptor.h"
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/SessionSettings.h"

int main(int argc, char** argv) {
    FIX::SessionSettings settings("apps/server/gateway.cfg");
    Gateway app;
    FIX::FileStoreFactory storeFactory(settings);
    FIX::FileLogFactory logFactory(settings);
    FIX::SocketAcceptor acceptor(app, storeFactory, settings, logFactory);

    acceptor.start();
    std::cout << "Exchange acceptor running..." << std::endl;
    std::cin.get();  // wait for Enter
    acceptor.stop();
}
