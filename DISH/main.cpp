#include <iostream>
#include <zmq.h>
#include <Windows.h> // Sleep

#define ZMQ_BUILD_DRAFT_API

using namespace std;

// DISH

int main() {

	cout << "zmq: " << zmq_has("draft") << endl;

	void* context = zmq_ctx_new();

	if (context == NULL) {
		cout << "null ctx" << endl;
		return -1;
	}

	void* dish = zmq_socket(context, ZMQ_DISH);
	if (dish == NULL) {
		cout << "null dish" << endl;
		return -1;
	}

	if (zmq_bind(dish, "udp://224.0.0.1:28650") == -1) {
		cout << "failed bind" << endl;
		return -1;
	}
	Sleep(300); // windows.h
	if (zmq_join(dish, "telemetry") == -1) {
		cout << "failed join" << endl;
		return -1;
	}

	zmq_msg_t msg;
	if (zmq_msg_init(&msg) == -1) {
		cout << "failed init msg" << endl;
		return -1;
	}

	cout << "before recv" << endl;

	int recv_rc = zmq_msg_recv(&msg, dish, 0);
	if (recv_rc == -1) {
		cout << "no bytes received" << endl;
		return -1;
	}
	else {
		cout << "successful receieve" << (char*)zmq_msg_data(&msg) << endl;
	}
	zmq_msg_close(&msg);
	zmq_close(dish);
	return 0;
}