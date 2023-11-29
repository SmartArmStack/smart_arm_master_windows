/**
A slightly upgraded version of packet 2 with two additions:
- Packet version, so that from now on the patient side can also distingish what is being received.
- Data of any number of additional key states added to the configuration.json.
*/
void UDPSender::send_packet_version_3()
{
    QByteArray buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);

    //Unique information
    s << qint32(3);//Packet version -- Hard coded version
    s << qint32(0);//Computer index
    s << qint32(0);//Cluch state, 0 or 1
    s << float(20.0);//Motion scaling, larger than zero but not enforced here.

    s << qint32(0);//Number of additional keys, in this case none.
    for(auto& additional_key_and_state: additional_virtual_key_codes_and_states_)
    {
        s << qint32(std::get<1>(additional_key_and_state));//The state of each additional key
    }

    s << qint32(2);//Number of master manipulators, usually 1 or 2

    //For each master manipulator
    for(int manipulator_index=0;manipulator_index < 2;manipulator_index++)
    {
            s << qint32(manipulator_index);

            const DQ t = manipulator->get_translation();
            const DQ r = manipulator->get_rotation();
            const DQ t_dot = manipulator->get_linear_velocity();
            const DQ r_dot = manipulator->get_angular_velocity();
      
            s   << float(t.q(1))
                << float(t.q(2))
                << float(t.q(3))

                << float(r.q(0))
                << float(r.q(1))
                << float(r.q(2))
                << float(r.q(3))

                << float(t_dot.q(1))
                << float(t_dot.q(2))
                << float(t_dot.q(3))

                << float(r_dot.q(1))
                << float(r_dot.q(2))
                << float(r_dot.q(3))

                << float(manipulator->get_button())//Master button state

                << float(manipulator->get_gripper());//If there is a CONTEC gripper attached
        }
    }

    //Checksum
    quint16 crc16 = qChecksum(buffer,uint(buffer.size()));
    s << quint16(crc16);

    //Send
    QHostAddress ip;
    //Just an example of target IP
    if(ip.setAddress("192.168.0.1"))
    {
        //Example port
        int port = 2222;
        qint64 return_value = udp_socket_.writeDatagram(buffer, ip, quint16(port));
        if(return_value == -1)
        {
            std::runtime_error("Error sending packet");
        }
    }
}
