var cb_button = null;
var cb_data = null;

var button_reader = new function() {

    this.button = saul.get_by_name("button");

    var self = this;

    this.start = function () {
        self.button.on_threshold(1, this.callback, saul.op.EQ);
    };

    this.callback = function () {
        // Handle the data a bit, only send every 2 press
        now = timer.now();
        print("button: pressed (" + now + ")");

        if (cb_button) {
            cb_button(now);
        }
        return true;
    }
}
var main_app_prev_button_time = 0;
var main_app = new function() {
    var self = this;
    this.start = function () {
        cb_button = self.button_cb;
    };

    this.button_cb = function (now) {
        print("main: callback");
        diff = now - main_app_prev_button_time;
        main_app_prev_button_time = now;

        if (diff < 500000) {
            print("main: double click");
            if (cb_data) {
                cb_data(diff);
            }
        }
        return true;
    }
}


var publisher_app = new function() {
    var self = this;
    this.start = function () {
        cb_data = self.publish_data;
    };

    this.publish_data = function (value) {
        print("publish: event CB: " + value);
        // PUT 3
        payload = value.toString();
        retval = coap.request("coap://[2001:db8::7b65:3b4c:f3bb:eea2]:5683/click", coap.method.PUT, payload);
	print("data received: " + retval);
        return true;
    }
}
