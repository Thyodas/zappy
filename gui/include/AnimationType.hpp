/*
** EPITECH PROJECT, 2023
** gui
** File description:
** AnimationType
*/

#ifndef ANIMATIONTYPE_HPP_
    #define ANIMATIONTYPE_HPP_

namespace GUI {
    enum AnimationType {
        ANIM_CROUNCH,
        ANIM_DIE,
        ANIM_IDLE,
        ANIM_KICK,
        ANIM_TPOSE,
        ANIM_SPELL,
        ANIM_SCREAM,
        ANIM_WALKING,
        ANIM_END // used to know if an action is done
    };
    enum Direction {
        D_VOID,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
};

#endif /* !ANIMATIONTYPE_HPP_ */
