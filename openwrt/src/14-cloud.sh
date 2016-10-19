#! /bin/sh

if ["$ACTION" = "ifup"] ; then
  uuid=`cat /etc/cloud/uuid`;
  version=`cat /etc/cloud/version`;

  action="signin";
  host="iot.aaoo-tech.com";
  sub_topic="/yun/$uuid/"
  pub_topic="/yun/";

  wget http://ipinfo.io/ip -qO /etc/cloud/public_ip || exit;
  public_ip=`cat /etc/cloud/public_ip`;

  msg='{"action": "'$action'", "data": {"id": "'$uuid'", "ip": "'$public_ip'", "version": "'$version'"}}';
  # [TODO] replace with customzied application
  # mosquitto_sub -h "$host" -t "$sub_topic" 
  mosquitto_pub -h "$host" -t "$pub_topic" -m "$msg";

fi