#include "x_library_socket_base.h"

namespace xM
{
    namespace x_socket
    {
        TcpCoreBase::TcpCoreBase()
        {
            listen_ = -1;
            event_ = nullptr;
            run_flag_ = false;
        }
        TcpCoreBase::~TcpCoreBase()
        {

        }

        TcpServerBase::TcpServerBase()
        {
            //
        }
        TcpServerBase::~TcpServerBase()
        {
            //
        }
    }
}