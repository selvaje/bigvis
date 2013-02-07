#include <Rcpp.h>
#include "group.hpp"
#include "summary.hpp"
using namespace Rcpp;

template<typename Group, typename Stat>
NumericVector summarise(const NumericVector& z, const NumericVector& weight, 
                        const Group& group, const Stat& stat) {
  int n_obs = group.size();
  int n_bins = group.nbins();

  const NumericVector& weight_ = (weight.size() > 0) ? weight : 
    rep(NumericVector::create(1), n_obs);
  const NumericVector& z_ = (z.size() > 0) ? z : 
    rep(NumericVector::create(1), n_obs);

  std::vector<Stat> stats(n_bins + 1, stat);
  for(int i = 0; i < n_obs; ++i) {
    int bin = group.bin(i);
    stats.at(bin).push(z_[i], weight_[i]);      
  }

  int m = stats[0].size();
  NumericMatrix res(n_bins, m);
  for (int i = 0; i < n_bins; ++i) {
    for (int j = 0; j < m; ++j) {
      res(i, j) = stats[i].compute(j);
    }
  }

  CharacterVector colnames(m);
  for (int j = 0; j < m; ++j) {
    colnames[j] = stats[0].name(j);
  }
  res.attr("dimnames") = List::create(CharacterVector::create(), colnames);

  return res;
}

Group2d<GroupFixed> Group2dFixed (const NumericVector& x, const NumericVector& y,
            double x_width, double y_width, 
            double x_origin = 0, double y_origin = 0) {

  return Group2d<GroupFixed>(
    GroupFixed(x, x_width, x_origin),
    GroupFixed(y, y_width, y_origin));
}

// -----------------------------------------------------------------------------
// Autogenerated by summarise-gen.r
// [[Rcpp::export]]
NumericVector summarise_count_breaks(const NumericVector& x, const NumericVector& z, const NumericVector& weight, NumericVector& breaks) {
  return summarise(z, weight, GroupBreaks(x, breaks), SummarySum(0));
}

// [[Rcpp::export]]
NumericVector summarise_count_fixed(const NumericVector& x, const NumericVector& z, const NumericVector& weight, double width, double origin) {
  return summarise(z, weight, GroupFixed(x, width, origin), SummarySum(0));
}

// [[Rcpp::export]]
NumericVector summarise_count_2dfixed(const NumericVector& x, const NumericVector& y, const NumericVector& z, const NumericVector& weight, double x_width, double y_width, double x_origin, double y_origin) {
  return summarise(z, weight, Group2dFixed(x, y, x_width, y_width, x_origin, y_origin), SummarySum(0));
}

// [[Rcpp::export]]
NumericVector summarise_sum_breaks(const NumericVector& x, const NumericVector& z, const NumericVector& weight, NumericVector& breaks) {
  return summarise(z, weight, GroupBreaks(x, breaks), SummarySum(1));
}

// [[Rcpp::export]]
NumericVector summarise_sum_fixed(const NumericVector& x, const NumericVector& z, const NumericVector& weight, double width, double origin) {
  return summarise(z, weight, GroupFixed(x, width, origin), SummarySum(1));
}

// [[Rcpp::export]]
NumericVector summarise_sum_2dfixed(const NumericVector& x, const NumericVector& y, const NumericVector& z, const NumericVector& weight, double x_width, double y_width, double x_origin, double y_origin) {
  return summarise(z, weight, Group2dFixed(x, y, x_width, y_width, x_origin, y_origin), SummarySum(1));
}

// [[Rcpp::export]]
NumericVector summarise_mean_breaks(const NumericVector& x, const NumericVector& z, const NumericVector& weight, NumericVector& breaks) {
  return summarise(z, weight, GroupBreaks(x, breaks), SummaryMoments(1));
}

// [[Rcpp::export]]
NumericVector summarise_mean_fixed(const NumericVector& x, const NumericVector& z, const NumericVector& weight, double width, double origin) {
  return summarise(z, weight, GroupFixed(x, width, origin), SummaryMoments(1));
}

// [[Rcpp::export]]
NumericVector summarise_mean_2dfixed(const NumericVector& x, const NumericVector& y, const NumericVector& z, const NumericVector& weight, double x_width, double y_width, double x_origin, double y_origin) {
  return summarise(z, weight, Group2dFixed(x, y, x_width, y_width, x_origin, y_origin), SummaryMoments(1));
}

// [[Rcpp::export]]
NumericVector summarise_sd_breaks(const NumericVector& x, const NumericVector& z, const NumericVector& weight, NumericVector& breaks) {
  return summarise(z, weight, GroupBreaks(x, breaks), SummaryMoments(2));
}

// [[Rcpp::export]]
NumericVector summarise_sd_fixed(const NumericVector& x, const NumericVector& z, const NumericVector& weight, double width, double origin) {
  return summarise(z, weight, GroupFixed(x, width, origin), SummaryMoments(2));
}

// [[Rcpp::export]]
NumericVector summarise_sd_2dfixed(const NumericVector& x, const NumericVector& y, const NumericVector& z, const NumericVector& weight, double x_width, double y_width, double x_origin, double y_origin) {
  return summarise(z, weight, Group2dFixed(x, y, x_width, y_width, x_origin, y_origin), SummaryMoments(2));
}

// [[Rcpp::export]]
NumericVector summarise_median_breaks(const NumericVector& x, const NumericVector& z, const NumericVector& weight, NumericVector& breaks) {
  return summarise(z, weight, GroupBreaks(x, breaks), SummaryMedian());
}

// [[Rcpp::export]]
NumericVector summarise_median_fixed(const NumericVector& x, const NumericVector& z, const NumericVector& weight, double width, double origin) {
  return summarise(z, weight, GroupFixed(x, width, origin), SummaryMedian());
}

// [[Rcpp::export]]
NumericVector summarise_median_2dfixed(const NumericVector& x, const NumericVector& y, const NumericVector& z, const NumericVector& weight, double x_width, double y_width, double x_origin, double y_origin) {
  return summarise(z, weight, Group2dFixed(x, y, x_width, y_width, x_origin, y_origin), SummaryMedian());
}

