

var express = require('express'),
  config = require('./config/config'),
  db = require('./app/models'),
  mqtt = require('mqtt');

var _ = require('underscore');

var app = express();

require('./config/express')(app, config);

db.sequelize
  .sync()
  .then(function () {
    app.listen(config.port, function () {
      console.log('Express server listening on port ' + config.port);
    });
  }).catch(function (e) {
    throw new Error(e);
  });

const client = mqtt.connect(config.mqtt.host)
client.on('connect', () => {
  console.log('MQTT server connected')
  client.subscribe('/yun/')
});

client.on('message', (topic, message) => {
  if (topic === '/yun/') {
    message = JSON.parse(message)
    
    if (_.isUndefined(message['action']) === true) {
      // do nothing
    } else {
      action = message['action'];
      data = message['data'];

      uuid = data.id;
      ip = data.ip;
      version = data.version;

      // [TODO] validate UUID

      db.History.create({
        uuid: uuid,
        ip: ip,
        version: version
      }).then((history) => {
      });

      // [TODO] determine the IP location

      client.publish('/yun/' + uuid + '/', JSON.stringify({
        'ip': '52.221.230.111',
        'version': '0.1.0'
      }));
    }
  }
})