// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently,
//  but are changed infrequently

#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0601
#endif

#define ASIO_STANDALONE
#include <asio-1.22.2\include\asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <mutex>
#include <string>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
