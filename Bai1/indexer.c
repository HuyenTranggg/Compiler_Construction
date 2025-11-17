#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Các hằng số cho kích thước tối đa của các mảng
#define MAX_INDEX_RECORDS 10000     
#define MAX_WORD_LEN 1000        
#define MAX_LINE_LEN 10000       
#define MAX_LINE_REF_LEN 3000 

// Cấu trúc để lưu một từ, số lần đếm, và danh sách dòng của nó.
typedef struct {
    char word[MAX_WORD_LEN];
    int count;
    char line_refs[MAX_LINE_REF_LEN];
} IndexEntry;

// Mảng chính lưu toàn bộ bảng chỉ mục
IndexEntry main_index[MAX_INDEX_RECORDS];
int entry_count = 0; // Biến đếm số lượng từ đã được thêm vào chỉ mục

// Mảng lưu danh sách các từ cần bỏ qua (stop words)
char stop_words_list[MAX_INDEX_RECORDS][MAX_WORD_LEN];
int stop_words_count = 0; // Biến đếm số lượng từ dừng

// Hàm kiểm tra một từ có nằm trong danh sách stop words không
int is_stop_word(const char *w) {
    for (int i = 0; i < stop_words_count; i++)
        if (strcmp(w, stop_words_list[i]) == 0) return 1;
    return 0;
}

// Hàm chuyển một chuỗi về dạng chữ thường
void convert_to_lowercase(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

// Hàm kiểm tra một từ có phải là danh từ riêng không
// Dựa vào điều kiện: viết hoa chữ đầu và không đứng sau dấu chấm
int is_proper_noun_type(const char *original_word, char prev_char) {
    return (isupper(original_word[0]) && prev_char != '.');
}

// Hàm tìm chỉ số của một từ đã có trong bảng chỉ mục
int find_word_in_index(const char *w) {
    for (int i = 0; i < entry_count; i++)
        if (strcmp(main_index[i].word, w) == 0) return i;
    return -1; // Trả về -1 nếu không tìm thấy
}

// Hàm thêm một từ vào bảng chỉ mục hoặc cập nhật từ đã có
void process_word(const char *w, int line) {
    int pos = find_word_in_index(w);

    char line_str[12];
    snprintf(line_str, sizeof(line_str), "%d", line);

    // Nếu từ chưa có trong chỉ mục, thêm nó vào
    if (pos == -1) { 
        strncpy(main_index[entry_count].word, w, MAX_WORD_LEN - 1);
        main_index[entry_count].count = 1;
        strncpy(main_index[entry_count].line_refs, line_str, MAX_LINE_REF_LEN - 1);
        entry_count++;
    } 
    // Nếu từ đã có, cập nhật số lần đếm và danh sách dòng
    else { 
        main_index[pos].count++;
        // Nối thêm số dòng vào chuỗi, có kiểm tra độ dài để tránh bị tràn
        if (strlen(main_index[pos].line_refs) + strlen(line_str) + 3 < MAX_LINE_REF_LEN) {
            strcat(main_index[pos].line_refs, ", ");
            strcat(main_index[pos].line_refs, line_str);
        }
    }
}

// Hàm so sánh cho qsort, để sắp xếp các từ theo thứ tự alphabet
int compare_entries(const void *a, const void *b) {
    return strcmp(((IndexEntry*)a)->word, ((IndexEntry*)b)->word);
}

// Hàm main
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Cach dung: %s <file_van_ban> <file_output>\n", argv[0]);
        return 1;
    }

    // Mở file stop words và file văn bản
    FILE *stopwords_fp = fopen("stopw.txt", "r");
    FILE *text_fp = fopen(argv[1], "r");

    if (!stopwords_fp) {
        printf("Khong mo duoc stopw.txt\n");
        return 1;
    }
    if (!text_fp) {
        printf("Khong mo duoc file van ban: %s\n", argv[1]);
        return 1;
    }

    // Đọc toàn bộ file stop words vào mảng
    while (fscanf(stopwords_fp, "%999s", stop_words_list[stop_words_count]) != EOF) {
        convert_to_lowercase(stop_words_list[stop_words_count]);
        stop_words_count++;
    }
    fclose(stopwords_fp);

    // Bắt đầu đọc và xử lý file văn bản chính
    char line_buf[MAX_LINE_LEN];
    int line_num = 0;

    while (fgets(line_buf, sizeof(line_buf), text_fp)) {
        line_num++;
        int len = strlen(line_buf);

        char word_buf[MAX_WORD_LEN];
        int word_idx = 0;

        // Vòng lặp duyệt qua từng ký tự của dòng để tách từ
        for (int i = 0; i <= len; i++) {
            // Nếu là chữ cái thì thêm vào từ đang xử lý
            if (isalpha(line_buf[i])) {
                if (word_idx < MAX_WORD_LEN - 1)
                    word_buf[word_idx++] = line_buf[i];
            } 
            // Nếu là ký tự phân cách (không phải chữ cái)
            else {
                // Nếu có từ trong buffer thì xử lý nó
                if (word_idx > 0) {
                    word_buf[word_idx] = '\0'; // Đặt ký tự kết thúc chuỗi
                    char prev_char = (i > 0 ? line_buf[i - 1] : ' ');
                    
                    char lower_word_buf[MAX_WORD_LEN];
                    strncpy(lower_word_buf, word_buf, MAX_WORD_LEN);
                    convert_to_lowercase(lower_word_buf);
                    
                    // Chỉ xử lý từ nếu nó không phải danh từ riêng và không phải stop word
                    if (!is_proper_noun_type(word_buf, prev_char) && !is_stop_word(lower_word_buf))
                        process_word(lower_word_buf, line_num);
                        
                    word_idx = 0; // Reset buffer để bắt đầu từ mới
                }
            }
        }
    }
    fclose(text_fp);

    // Sắp xếp lại toàn bộ bảng chỉ mục
    qsort(main_index, entry_count, sizeof(IndexEntry), compare_entries);

    // Mở file output để ghi kết quả
    FILE *output_fp = fopen(argv[2], "w");
    if (!output_fp) {
        printf("Khong the tao file output: %s\n", argv[2]);
        return 1;
    }

    // Vòng lặp để in kết quả ra màn hình và ghi ra file
    for (int i = 0; i < entry_count; i++) {
        // Giữ nguyên định dạng output
        printf("%-12s %d %s\n", main_index[i].word, main_index[i].count, main_index[i].line_refs);
        fprintf(output_fp, "%-12s %d %s\n", main_index[i].word, main_index[i].count, main_index[i].line_refs);
    }

    fclose(output_fp);
    printf("Da xuat ket qua ra file: %s\n", argv[2]);
    return 0;
}
