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
