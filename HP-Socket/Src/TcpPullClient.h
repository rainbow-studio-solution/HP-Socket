/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Version	: 3.3.2
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Project	: https://github.com/ldcsaa
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include "TcpClient.h"
#include "../../Common/Src/bufferpool.h"

class CTcpPullClient : public IPullClient, public CTcpClient
{
public:
	virtual EnFetchResult Fetch	(BYTE* pData, int iLength);
	virtual EnFetchResult Peek	(BYTE* pData, int iLength);

protected:
	virtual EnHandleResult FireReceive(IClient* pClient, const BYTE* pData, int iLength);

	virtual void Reset(BOOL bAll = TRUE)
	{
		m_iTotalLength = 0;
		m_lsBuffer.Clear();

		return __super::Reset(bAll);
	}

public:
	CTcpPullClient(ITcpClientListener* psoListener)
	: CTcpClient	(psoListener)
	, m_lsBuffer	(m_itPool)
	, m_iTotalLength(0)
	{

	}

	virtual ~CTcpPullClient()	{if(HasStarted()) Stop();}

private:
	int			m_iTotalLength;
	TItemList	m_lsBuffer;
};
