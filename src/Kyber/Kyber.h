/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class Kyber which contains the implementation of the Kyber cryptosystem
 */

#pragma once

#include "../Components/NTT.h"
#include "../Components/Keccak.h"
#include "../Components/PWMUnit.h"
#include "../Components/EncDecUnit.h"
#include "../Components/SamplingUnit.h"
#include "../Components/CompressorUnit.h"

#include "../DataStructures/Bytes.h"
#include "../DataStructures/Matrix.h"

class Kyber {
 public:
  Kyber(int option, const std::vector<int>& seed = {});
  std::pair<Bytes, Bytes> KeyGen();
  
  
  
  
 private:
  Bytes GenerateSeed_(int seed_size) const;
  std::vector<Bytes> GenerateRhoSigma_(const Bytes& seed) const;
  Matrix<Polynomial<int>> applyNTTMatrix_(const Matrix<Polynomial<int>>& matrix, int k) const;

  int n_;
  int q_;
  int k_;
  int n1_;
  int n2_;
  int du_;
  int dv_;
  std::unique_ptr<NTT> ntt_ = nullptr;
  std::unique_ptr<Keccak> keccak_ = nullptr;
  std::unique_ptr<PWMUnit> pwm_unit_ = nullptr;
  std::unique_ptr<EncDecUnit> encdec_unit_ = nullptr;
  std::unique_ptr<SamplingUnit> sampling_unit_ = nullptr;
  std::unique_ptr<CompressorUnit> compressor_unit_ = nullptr;

  std::unique_ptr<Bytes> pk_ = nullptr;
  std::unique_ptr<Bytes> sk_ = nullptr;
  
  std::vector<int> seed_ = {};

};