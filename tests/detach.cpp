#include <Sockets/TcpSocket.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/ListenSocket.h>
#include <Sockets/Utility.h>
#include <iostream>

class EchoSocket : public TcpSocket
{
public:
  EchoSocket(ISocketHandler& h) : TcpSocket(h) {
    SetLineProtocol();
  }

  void OnAccept() {
//    std::cout << "OnAccept #" << Utility::ThreadID() << std::endl;
    if (!Detach())
      std::cerr << "Detach() failed" << std::endl;
/*
    else
      std::cout << "Detach() OK" << std::endl;
    std::cout << "  IsDetach(): " << (IsDetach() ? "true" : "false") << std::endl;
*/
  }

  void OnDetached() {
//    std::cout << "OnDetached" << std::endl;
  }

  void OnLine(const std::string& line) {
//    std::cout << "OnLine #" << Utility::ThreadID() << std::endl;
    Send(line + "\n");
    SetCloseAndDelete();
  }

  void OnDelete() {
//    std::cout << "OnDelete" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  SocketHandler h;
  ListenSocket<EchoSocket> l(h);
  l.Bind(10244);
  h.Add(&l);
  while (true)
    h.Select();
}

