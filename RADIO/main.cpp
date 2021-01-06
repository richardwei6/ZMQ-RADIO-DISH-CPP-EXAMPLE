#include <iostream>
//#include "zmq.hpp"
#include <zmq.h>
#include <string>
#include <Windows.h>


using namespace std;

// RADIO

void assert(bool a) {
	if (!a) {
		cout << "failed - " << zmq_errno << endl;
		throw;
	}
}

int main() {
	void* context = zmq_ctx_new();
	assert(context != nullptr);
	int rc = zmq_ctx_set(context, ZMQ_IO_THREADS, 1);
	assert(rc == 0);

	void* radio = zmq_socket(context, ZMQ_RADIO);
	assert(radio != nullptr);

	rc = zmq_connect(radio, "udp://224.0.0.1:28650");
	assert(rc == 0);

	cout << "init success" << endl;

	while (1) {
		string t = "Test string";
		
		zmq_msg_t msg;
		rc = zmq_msg_init(&msg);
		assert(rc == 0);
		rc = zmq_msg_init_size(&msg, t.size());
		assert(rc == 0);
		if (t.size()) {
			memcpy(zmq_msg_data(&msg), t.data(), t.size());
		}

		rc = zmq_msg_set_group(&msg, "telemetry");
		assert(rc == 0);

		cout << "sending now" << endl;

		int b = zmq_msg_send(&msg, radio, 0);
		cout << "sent bytes - " << b << endl;
		//rc = zmq_msg_init_size(&);
		Sleep(100);
	}



	/*zmq::context_t ctx(1);
	zmq::socket_t r(ctx, ZMQ_RADIO);

	r.connect("udp://224.0.0.1:28650");
	while (1) {
		string t = "Test string";
		zmq::message_t msg{ t.data(), t.size() };
		msg.set_group("telemetry");
		cout << "sending data" << endl;
		r.send(msg, 0);
		//zmq_msg_send(msg.handle(), r.handle(), 0);
		Sleep(100);
	}*/

	return 0;
}