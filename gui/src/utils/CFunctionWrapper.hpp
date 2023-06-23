/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** CFunctionWrapper.hpp
*/

#pragma once

#include <iostream>
#include <sys/socket.h>

#ifdef __APPLE__
    #include <sys/select.h>
    #define __CONST_SOCKADDR_ARG const struct sockaddr *
#endif

int c_connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
int c_select(int __nfds, fd_set *__restrict __readfds,
             fd_set *__restrict __writefds, fd_set *__restrict __exceptfds,
             struct timeval *__restrict __timeout);
