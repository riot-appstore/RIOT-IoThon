service={"consumer": consumer_app};
producer_app.start(service);
consumer_app.start(service);
publisher_app.start();
main_app.start()
button_reader.start();

