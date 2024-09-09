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

#include <stdarg.h>

#include "../../.conf/constants_values.h"

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
  Kyber(int option, const std::vector<int>& seed = {}, int n = 256, int q = 3329, int k = 2,
  int n1 = 3, int n2 = 2, int du = 10, int dv = 4, bool benchmarking = false);

  std::pair<Bytes, Bytes> KeyGen();
  Bytes Encryption(const Bytes& pk, const Bytes& message, const Bytes& seed);  
  Bytes Decryption(const Bytes& sk, const Bytes& ciphertext);

  std::map<std::string, double> GetTimeResults() const { 
    std::map<std::string, double> results;
    for (auto& [key, value] : time_results_) {
      double sum = 0;
      for (auto& time : value) {
        sum += time;
      }
      results[key] = sum / value.size();
    }
    return results;
  }

 protected:
  Bytes GenerateSeed_(int seed_size) const;
  std::pair<Bytes, Bytes> GenerateRhoSigma_(const Bytes& seed) const;
  Matrix<Polynomial<int>> applyNTTMatrix_(const Matrix<Polynomial<int>>& matrix, int k, bool is_ntt = true) const;
  
  void InitializeConstants(int option);

  int n_;
  int q_;
  int k_;
  int n1_;
  int n2_;
  int du_;
  int dv_;
  
  std::unique_ptr<NTT> ntt_ = nullptr;
  std::unique_ptr<PWMUnit> pwm_unit_ = nullptr;
  std::unique_ptr<EncDecUnit> encdec_unit_ = nullptr;
  std::unique_ptr<SamplingUnit> sampling_unit_ = nullptr;
  std::unique_ptr<CompressorUnit> compressor_unit_ = nullptr;

  std::unique_ptr<Bytes> pk_ = nullptr;
  std::unique_ptr<Bytes> sk_ = nullptr;
  
  std::vector<int> seed_ = {};

  std::map<std::string, std::vector<double>> time_results_ {
    {"KeyGen", {}},
    {"Encryption", {}},
    {"Decryption", {}},
    {"KEMKeyGen", {}},
    {"KEMEncapsulation", {}},
    {"KEMDecapsulation", {}}
  };
};