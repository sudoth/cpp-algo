#ifndef MERGE_H
#define MERGE_H
template <typename T, typename U, typename V>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, V* out) {
  int it1 = 0;
  int it2 = 0;
  while (first_begin + it1 < first_end && second_begin + it2 < second_end) {
    if (*(first_begin + it1) < *(second_begin + it2)) {
      out[it1 + it2] = *(first_begin + it1);
      it1++;
    } else {
      out[it1 + it2] = *(second_begin + it2);
      it2++;
    }
  }
  while (first_begin + it1 < first_end) {
    out[it1 + it2] = *(first_begin + it1);
    it1++;
  }
  while (second_begin + it2 < second_end) {
    out[it1 + it2] = *(second_begin + it2);
    it2++;
  }
}
#endif