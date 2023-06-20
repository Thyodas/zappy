/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** cFunctionWrapper.cpp
*/

#include "CFunctionWrapper.hpp"

int c_connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
{
    return connect(__fd, __addr, __len);
}

int c_select(int __nfds, fd_set *__restrict __readfds,
             fd_set *__restrict __writefds,
             fd_set *__restrict __exceptfds,
             struct timeval *__restrict __timeout)
{
    return select(__nfds, __readfds, __writefds, __exceptfds, __timeout);
}
