global_f = null
var producer_app = new function() {
    this.button = saul.get_by_name("button");
    this.led = saul.get_by_name("led");
    this.temp_sensor = saul.get_by_name("temp_sensor");

    var self =  this;
    buttonState = true;
    
    this.start = function (services) {
        //var handler;

	//Start producer
    global_f = services["consumer"].consumer
	this.producer(services);
    };
   

    this.producer = function(service) {

        var callback = function (service) {
            print("button_pressed");
            temp_value = self.temp_sensor.get_value();
            global_f();
	    print(temp_value);
            return true;
        }

        print("Waiting...");
        self.button.on_threshold(0, callback, saul.op.EQ);
    }
}
var consumer_app = new function() {
    this.start = function (services) {
    };
    this.consumer = function () {
        print("Process data here!");
    };
}


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
        coap.request("coap://[2001:470:749d:2:7b76:4044:da06:8aba]/click", coap.method.PUT, payload);
//        coap.request("coap://[fe80::7b76:4044:da06:8aba]/riot/board", 3, payload);
//        retval = coap.request("coap://[fe80::7b76:4044:da06:8aba]:5683/riot/board", coap.method.GET, "276896");
//	print("data received: " + retval);
        return true;
    }
}

service={"consumer": consumer_app};
producer_app.start(service);
consumer_app.start(service);
publisher_app.start();
main_app.start()
button_reader.start();

