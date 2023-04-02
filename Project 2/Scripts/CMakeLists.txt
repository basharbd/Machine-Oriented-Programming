cmake_minimum_required(VERSION 3.17.5)
project(FinalCardsYonok C)

set(CMAKE_C_STANDARD 99)

add_executable(FinalCardsYonok Game.c ControlTheGame.c main.c test.c)