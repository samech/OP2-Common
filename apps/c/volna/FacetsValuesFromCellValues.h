void FacetsValuesFromCellValues(double *CellLeft, double *CellRight,
                double *LeftFacetValues, //OP_WRITE
                double *RightFacetValues, //OP_WRITE
                double *InterfaceBathy, //OP_WRITE
                double *mesh_FacetNormals, int *isRightBoundary //OP_READ
                /*,double *t*/
//EZ PARA, the FacetNormals are only required on boudnary edges.... redundant data movement - split???
 )
{
  LeftFacetValues[0] = CellLeft[0];
  LeftFacetValues[1] = CellLeft[1];
  LeftFacetValues[2] = CellLeft[2];
  LeftFacetValues[3] = CellLeft[3];

  if (!isRightBoundary) {
    RightFacetValues[0] = CellRight[0];
    RightFacetValues[1] = CellRight[1];
    RightFacetValues[2] = CellRight[2];
    RightFacetValues[3] = CellRight[3];
  } else {
    RightFacetValues[3] = CellLeft[3];
    double nx = mesh_FacetNormals[0];
    double ny = mesh_FacetNormals[1];
    double inNormalVelocity = CellLeft[1] * nx + CellLeft[2] * ny;
    double inTangentVelocity = CellLeft[1] * ny + CellLeft[2] * nx;

    double outNormalVelocity;
    double outTangetVelocity;

    //WALL
    RightFacetValues[0] = CellLeft[0];
    outNormalVelocity = -1.0 * inNormalVelocity;
    outTangetVelocity = inTangentVeolcity;


    /* //HEIGHTSUBC
    RightFacetValues[0] = -1.0 * RightFacetValues[3];
    RightFacetValues[0] += 0.1 * sin(10.0*t);
    outNormalVelocity = inNormalVelocity;
    outNormalVelocity +=
        2.0 * sqrt( params_g * CellLeft[0] );
    outNormalVelocity -=
        2.0 * sqrt( params_g * RightFacetValues[0] );

    outTangentVelocity = inTangentVelocity;
    */ //end HEIGHTSUBC

    /* //FLOWSUBC
    outNormalVelocity = 1;

    //RightFacetValues[0] = - RightFacetValues[3];

    RightFacetValues[0] = (inNormalVelocity - outNormalVelocity);
    RightFacetValues[0] *= .5 / sqrt( params_g );

    RightFacetValues[0] += sqrt( CellLeft[0] );

    outTangentVelocity = inTangentVelocity;
    */

    RightFacetValues[1] = outNormalVelocity * nx - outTangentVelocity * ny;
    RightFacetValues[2] = outNormalVelocity * ny - outTangentVelocity * nx;
  }

  *InterfaceBathy = LeftFacetValues[3] > RightFacetValues[3] ? LeftFacetValues[3] : RightFacetValues[3];
}
