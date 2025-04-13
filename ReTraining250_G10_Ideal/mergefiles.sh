#!/bin/bash

mkdir MakeNTuples250_beta_G05
hadd MakeNTuples250_beta_G05/light_quark_merged.root *light*root
hadd MakeNTuples250_beta_G05/b_quark_merged.root *b*root
hadd MakeNTuples250_beta_G05/c_quark_merged.root *c*root
