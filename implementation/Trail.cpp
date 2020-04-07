
#include "Trail.h"


Trail::Trail() {
   this->length = 0; 
}

Trail::~Trail() {
   for(int i = 0; i < length; ++i){
      delete breadcrumbs[i];
   }
}

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   return breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) {
   if(length < TRAIL_ARRAY_MAX_SIZE){
      breadcrumbs[length] = t;
      length += 1;
   }
}

bool Trail::contains(int x, int y) {
   for(int i = 0; i < length; ++i){
      if(breadcrumbs[i] != nullptr){
         if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y){
            return true;
         }
      }
   }
   return false;
}

Breadcrumb* Trail::getIndex(int x, int y) {
   for(int i = 0; i < length; ++i){
      if(breadcrumbs[i] != nullptr){
         if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y){
            return breadcrumbs[i];
         }
      }
   }
   return nullptr;
}
