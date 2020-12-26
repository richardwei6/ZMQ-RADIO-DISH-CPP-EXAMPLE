#include <iostream>
#include <zmq.h>

#define ZMQ_BUILD_DRAFT_API

using namespace std;

// DISH

int main() {
	void* context = zmq_ctx_new();
	void* dish = zmq_socket(context, ZMQ_DISH);
	if (zmq_bind(dish, "tcp://*:5556") == -1) {
		cout << "failed bind" << endl;
		return -1;
	}
	if (zmq_join(dish, "TV") == -1) {
		cout << "failed join" << endl;
		return -1;
	}
	int bytesReceieved;
	zmq_msg_t msg;
	zmq_msg_init(&msg);
	cout << "before recv" << endl;
	bytesReceieved = zmq_msg_recv(&msg, dish, 0);
	if (bytesReceieved == -1) {
		cout << "no bytes received" << endl;
		return -1;
	}
	else {
		cout << "successful receieve" << (char*)zmq_msg_data(&msg) << endl;
	}
	cout << "finishing" << endl;
	zmq_msg_close(&msg);
	zmq_ctx_destroy(context);
	return 0;
}