// Example model


module.exports = function (sequelize, DataTypes) {

  var History = sequelize.define('History', {
    uuid: DataTypes.STRING,
    ip: DataTypes.STRING,
    version: DataTypes.STRING
  }, {
    classMethods: {
    }
  });

  return History;
};

