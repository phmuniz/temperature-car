document.addEventListener("DOMContentLoaded", function() {
    console.log("script carregado.");
    
    let connection = new WebSocket("ws://10.0.0.101:81", ['arduino']);

    // escuta menssagem do ESP8266
    connection.onmessage = function(messageEvent) {
        console.log(messageEvent.data);
    }

    /**
     * connection.send envia menssagem para o ESP8266
     * onmousedown é um evento que ocorre quando um elemento recebe um clique
     * onmouseup ocorre quanto o botão do mouse deixa de ser pressionado e remove o clique do elemento
     *  */

    const frontButton = document.getElementById("front");
    frontButton.onmousedown = function(event) {
        connection.send("FRONT");
    }
    frontButton.onmouseup = function(event) {
        connection.send("OFF");
    }

    const leftButton = document.getElementById("left");
    leftButton.onmousedown = function(event) {
        connection.send("LEFT");
    }
    leftButton.onmouseup = function(event) {
        connection.send("OFF");
    }

    const rightButton = document.getElementById("right");
    rightButton.onmousedown = function(event) {
        connection.send("RIGHT");
    }
    rightButton.onmouseup = function(event) {
        connection.send("OFF");
    }

    const backButton = document.getElementById("back");
    backButton.onmousedown = function(event) {
        connection.send("BACK");
    }
    backButton.onmouseup = function(event) {
        connection.send("OFF");
    }

});
