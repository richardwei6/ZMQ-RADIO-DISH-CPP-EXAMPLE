#include <iostream>
#include <zmq.h>
#include <string>

using namespace std;

// RADIO

int main() {
	void* context = zmq_ctx_new();
	void* radio = zmq_socket(context, ZMQ_RADIO);
	if (zmq_connect(radio, "tcp://127.0.0.1:5556") == -1) {
		cout << "failed connect" << endl;
		return -1;
	}
	zmq_msg_t msg;
	const char* content = "text";
	if (zmq_msg_init_data(&msg, &content, strlen(content), NULL, NULL)) {
		cout << "failed init" << endl;
		return -1;
	}

	if (zmq_msg_set_group(&msg, "TV") == -1) {
		cout << "failed set group" << endl;
		return -1;
	}
	cout << "sending now" << endl;
	if (zmq_msg_send(&msg, radio, 0) == -1) {
		zmq_msg_close(&msg);
		cout << "failed to send" << endl;
		return -1;
	}
	else {
		cout << "sent" << endl;
	}

	zmq_ctx_destroy(context);
	//zmq_msg_close(&msg);

	return 0;
}