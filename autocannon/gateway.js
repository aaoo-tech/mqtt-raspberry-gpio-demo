const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://iot.aaoo-tech.com')

client.on('connect', () => {
  client.subscribe('/yun')
})

client.on('message', (topic, message) => {
  if (topic === '/yun') {
    var _message = JSON.parse(message)

    console.log(_message);
  }
})

var turnOnLight = () => {
  console.log('light on')
  client.publish('/yun/router/cloudriver-router/cloudriver-device', JSON.stringify({
    'action': 'turnon'
  }))
}

var turnOffLight = () => {
  console.log('light off')
  client.publish('/yun/router/cloudriver-router/cloudriver-device', JSON.stringify({
    'action': 'turnoff'
  }))
}

var status = true
setInterval(() => {
  if (status) {
    turnOffLight()
  } else {
    turnOnLight()
  }

  status = ! status
}, 10000)