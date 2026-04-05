// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_WALL_HPP
#define CRABS_WALL_HPP
#include <_Config.h>
#if SEAM >= CRABS_DIC
#include "Door.hpp"
#include "Op.hpp"
#include "Array.hpp"
#define WAL_A typename T = ISW, typename ISZ = ISN
#define WAL_P T, ISZ
#define WAL TWall<T, ISZ>
namespace _ {
  
/* A group of Doors that share the same Extended Types.
Only one single wall is required for a Chinese Room, but when more memory is
needed a new Wall may be created and destroyed dynamically.

@code
+--------------+
|  Terminals   |
|      v       |
|vvvvvvvvvvvvvv|
|    Boofer    |
|^^^^^^^^^^^^^^|
|      ^       |
|  TStack of   |
|    Doors     |
|   Offsets    |
|--------------|
|    Header    |
+--------------+
@endcode */
template<typename ISZ = ISM, typename ISY = ISN>
class TWall : public Operand {
 public:
  enum {
    BytesMin = 512,  //< Min functional Wall size.
  };

private:
  IUD ctx_; //< Plain Context Type remap word.
  TStack<TDoor<ISZ>, ISZ, ISY> doors_;  //< The doors in the room.
	BOL is_dynamic_;	//< Whether this wall was dynamically allocated or not.

  //virtual ~TWall() {
  //  if (is_dynamic_) {
  //    CHA* socket = TPtr<CHA>(&doors_);
  //    delete[] socket;
  //  }
  //}

  TWall(ISW bytes = BytesMin) : 
      is_dynamic_(true) {
    bytes = bytes < BytesMin ? ISC(BytesMin) : bytes;
    ISW size_words = (bytes >> ACPUBytesLog2) + 3;
    IUW *socket = new IUW[size_words];
    doors_ = TStackInit<TDoor<ISZ>, ISZ, ISY>(socket, bytes);
  }

  /* Constructs a wall from the given block of words. */
  TWall(IUW* socket, ISW bytes) {
    TStackInit(TPtr<TStack<TDoor<ISZ>, ISZ, ISY>>(socket), bytes);
  }

  /* Gets the size of the wall in bytes. */
  ISW GetSizeBytes() {
    return doors_.GetSizeBytes();
  }
  /* Gets a pointer to the array of pointers to Door(). */
  TStack<TDoor<ISZ>, ISZ, ISY >* Doors() {
    return &doors_;
  }

  /* Gets the Door from the Door at the given index. */
  TDoor<ISZ> GetDoor(ISY index) { return 0; }

  /* Adds a Door to the slot.
  @return Returns nil if the Door is full and a pointer to the Door in the
          socket upon success. */
  ISC OpenDoor(TDoor<ISZ>* door) { return 0; }

  /* Deletes the Door from the Door at the given index. */
  BOL CloseDoor(ISY index) { return false; }

  /* Prints the given Door to the stream. */
  template<typename Printer>
  Printer& PrintTo(Printer & o) {
    return o;
  }
};

}  //< namespace _
#endif
#endif
