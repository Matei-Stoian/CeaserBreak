# Ceaser Chiper
This is my approach of implementing the a method of craking the Ceasar algorithm using the Chi-Squared distance. If you want to learn more you can checkout this article (https://ibmathsresources.com/2014/06/15/using-chi-squared-to-crack-codes/)

## Introduction
This report analyzes the performance of three distance metrics (Chi-squared, Euclidean, and Cosine) for breaking Caesar ciphers. We tested these methods on texts of different lengths with various shift values to evaluate their effectiveness.

## Methodology
We encrypted sample texts using the Caesar cipher with shifts of 3, 7, 13, and 21, then attempted to decrypt them using each distance metric. The texts ranged from short (~25 characters) to long (~450 characters), including cases with unusual letter distributions.

## Results

### Text Length Impact
- **Short texts** (< 30 chars): All methods struggled with very short texts, often failing to identify the correct shift due to insufficient frequency data.
- **Medium texts** (100-150 chars): Improved accuracy across all methods, with Chi-squared generally performing best.
- **Long texts** (200+ chars): Highest accuracy for all methods, with Chi-squared consistently finding the correct shift in the top position.

### Method Comparison

| Method | Overall Success Rate | Best With | Weaknesses |
|--------|---------------------|-----------|------------|
| Chi-squared | Highest | Medium to long texts | Can be misled by unusual distributions |
| Euclidean | Good | Longer texts | Less reliable with short texts |
| Cosine | Moderate | Works across text types | Generally less accurate than Chi-squared |

### Edge Cases
1. **Repetitive text**: Texts with unusual repetitive patterns caused problems for all methods, with Euclidean distance showing slightly better performance.
2. **Unusual letter frequency**: Texts lacking common English letters (E, T, A) or with high frequencies of uncommon letters confused all methods, with Chi-squared showing the most resilience.

## Conclusion
Chi-squared distance is generally the most effective method for breaking Caesar ciphers through frequency analysis, particularly with texts of sufficient length. While no method works perfectly for very short texts, all three methods become increasingly reliable as text length increases.

For optimal results:
- Use Chi-squared distance when analyzing texts of 100+ characters.
- Consider trying multiple methods for shorter texts or texts with unusual patterns.
- Be cautious with very short texts (under 25 characters), as frequency analysis may be unreliable regardless of method.
