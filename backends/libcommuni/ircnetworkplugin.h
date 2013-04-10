/**
 * XMPP - libpurple transport
 *
 * Copyright (C) 2013, Jan Kaluza <hanzz.k@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#pragma once

#include "transport/config.h"
#include "transport/networkplugin.h"
#include "session.h"
#include <QtCore>
#include <QtNetwork>
#include "Swiften/EventLoop/Qt/QtEventLoop.h"
#include "ircnetworkplugin.h"


class IRCNetworkPlugin : public QObject, public NetworkPlugin {
	Q_OBJECT

	public:
		IRCNetworkPlugin(Config *config, Swift::QtEventLoop *loop, const std::string &host, int port);

		void handleLoginRequest(const std::string &user, const std::string &legacyName, const std::string &password);

		void handleLogoutRequest(const std::string &user, const std::string &legacyName);

		void handleMessageSendRequest(const std::string &user, const std::string &legacyName, const std::string &message, const std::string &/*xhtml*/, const std::string &/*id*/);

		void handleJoinRoomRequest(const std::string &user, const std::string &room, const std::string &nickname, const std::string &password);

		void handleLeaveRoomRequest(const std::string &user, const std::string &room);

		void handleRoomSubjectChangedRequest(const std::string &user, const std::string &room, const std::string &message);

		void tryNextServer();

	public slots:
		void readData();
		void sendData(const std::string &string);

	private:
		MyIrcSession *createSession(const std::string &user, const std::string &hostname, const std::string &nickname, const std::string &password, const std::string &suffix = "");
		std::string getSessionName(const std::string &user, const std::string &legacyName);
		std::string getTargetName(const std::string &legacyName);

	private:
		Config *config;
		QTcpSocket *m_socket;
		std::map<std::string, MyIrcSession *> m_sessions;
		std::vector<std::string> m_servers;
		int m_currentServer;
		std::string m_identify;
		bool m_firstPing;
};
