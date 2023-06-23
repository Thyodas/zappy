/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** request.h
*/

#pragma once

#include <stdarg.h>
#include <stdlib.h>

#include "types.h"

ssize_t send_data(int fd, void *data, size_t len);
