#pragma once
#include "piece.h"
#include "position.h"

class Move {
  Position start_;
  Position end_;
  Piece piece_;
};