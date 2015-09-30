/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "ns3/ndnSIM-module.h"
#include "ns3/integer.h"
#include "ns3/string.h"

#include "ndns-daemon.hpp"

namespace ns3 {
namespace ndn {

namespace daemon = ::ndn::ndns;

class NdnsServerApp : public Application
{
public:
  static TypeId
  GetTypeId()
  {
    static TypeId tid = TypeId("NdnsServerApp")
      .SetParent<Application>()
      .AddConstructor<NdnsServerApp>()
      .AddAttribute("ConfigFile", "Path for the configuration file", StringValue("."),
                    MakeStringAccessor(&NdnsServerApp::m_configFile), MakeStringChecker());

    return tid;
  }

protected:
  // inherited from Application base class.
  virtual void
  StartApplication()
  {
    m_instance.reset(new daemon::NdnsDaemon(m_configFile));
  }

  virtual void
  StopApplication()
  {
    m_instance.reset();
  }

private:
  std::unique_ptr<daemon::NdnsDaemon> m_instance;
  std::string m_configFile;
};

} // namespace ndn
} // namespace ns3
