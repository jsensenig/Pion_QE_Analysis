//
// Created by Jon Sensenig on 12/4/20.
//

#ifndef PION_QE_SELECTIONS_H
#define PION_QE_SELECTIONS_H


class Selections {

public:
  Selections();
  virtual ~Selections();

  bool PIDACut( double pida );
  bool DaughterCut( int p, int n );
protected:

};


#endif //PION_QE_SELECTIONS_H
