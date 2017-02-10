var Alexa = require('alexa-sdk');
var http = require('http');
const skillName = "Light Control";

var options = {
    host:       'ditchfieldcaleb.com',
    path:       '/api/',
    method:     'HEAD'
};

var handlers = {

    "CommandIntent": function () {
        function getRandomInt(min, max) {
            return Math.floor(Math.random() * (max - min)) + min;
        }

        var speechOutput = "";
        console.log("Command: " + JSON.stringify(this.event.request.intent.slots.Command));
        if(this.event.request.intent.slots.Command.name && this.event.request.intent.slots.Command.name.toLowerCase() == "lights on") {
            options.path = "/api/AllOn";
            var req = http.request(options, function(res) {
                console.log("Request was made.");
            });
            req.end();
        } else if(this.event.request.intent.slots.Command.name && this.event.request.intent.slots.Command.name.toLowerCase() == "lights off") {
            options.path = "/api/AllOff";
            var httpreq = http.request(options, function(res) {
                console.log("Request was made.");
            });
            httpreq.end();
        } else {
            speechOutput = "Sorry, I don't know that command.." + this.event.request.intent.slots.Command.name;
        }
        this.emit(':tellWithCard', speechOutput, skillName, speechOutput);
    },

    "AboutIntent": function () {
        var speechOutput = "Caleb is awesome.";
        this.emit(':tellWithCard', speechOutput, skillName, speechOutput);
    },

    "AMAZON.HelpIntent": function () {
        var speechOutput = "";
        speechOutput += "Here are some things you can say: ";
        speechOutput += "Lights On.";
        speechOutput += "Lights Off.";
        speechOutput += "So how can I help?";
        this.emit(':ask', speechOutput, speechOutput);
    },

    "AMAZON.StopIntent": function () {
        var speechOutput = "Light control, exiting.";
        this.emit(':tell', speechOutput);
    },

    "AMAZON.CancelIntent": function () {
        var speechOutput = "Light control, exiting.";
        this.emit(':tell', speechOutput);
    },

    "LaunchRequest": function () {
        var speechText = "";
        speechText += "Welcome to " + skillName + ".  ";
        speechText += "Tell me what to do, Master.";
        var repromptText = "For instructions on what you can say, please say help me.";
        this.emit(':ask', speechText, repromptText);
    }

};

exports.handler = function (event, context) {
    var alexa = Alexa.handler(event, context);
    alexa.appId = "amzn1.ask.skill.b8959ba3-6e97-419d-942a-9e5035ccb9bb";
    alexa.registerHandlers(handlers);
    alexa.execute();
};
