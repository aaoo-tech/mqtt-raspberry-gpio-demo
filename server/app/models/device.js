// Example model


module.exports = function (sequelize, DataTypes) {

  var Device = sequelize.define('Device', {
    uuid: DataTypes.STRING,
  }, {
    classMethods: {
    }
  });

  return Device;
};

