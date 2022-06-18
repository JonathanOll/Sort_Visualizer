using namespace std;

#include "tri.hpp"
#include "list.hpp"
#include <vector>
#include <map>
#include <chrono>
#include <thread>


vector<void(*)(vector<Element>&)> functions;
map<void(*)(vector<Element>&), wstring> names;

vector<Element*> sublist(vector<Element> &l, int begin, int end) {
    if (end < begin) return vector<Element*>({});
    vector<Element*> res;
    for (int i = begin; i < end+1; i++) res.push_back(&l[i]);
    return res;
}

vector<Element*> sublist(vector<Element*> &l, int begin, int end) {
    if (end < begin) return vector<Element*>({});
    vector<Element*> res;
    for (int i = begin; i < end+1; i++) res.push_back(l[i]);
    return res;
}

void tri_selection(vector<Element> &l) {
    int n = l.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            if (l[j] < l[min]) min = j;
        }
        if (min != i) swap(l, i, min);
    }
}

void tri_insertion(vector<Element> &l) {
    for (int i = 0; i < l.size(); i++) {
        int x = l[i].getValue();
        int j = i;
        while (j > 0 && l[j-1] > x) {
            l[j] = l[j-1];
            j = j - 1;
        }
        l[j] = x;
    }
}

void tri_bulle(vector<Element> &l) {
    for (int i = l.size()-1; i > 1; i--) {
        for (int j = 0; j < l.size()-1; j++){
            if (l[j+1] < l[j]) {
                swap(l, j+1, j);
            }
        }
    }
}

void tri_shell(vector<Element> &l) {
    int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1};
    int n = l.size();
    for(int m : gaps) {
        for (int r = 0; r < m; r++) {
            for (int i = r+m; i < n; i += m) {
                int j = i;
                int x = l[i].getValue();
                while (j > r && l[j-m].getValue() > x) {
                    l[j] = l[j-m];
                    j = j - m;
                }
                l[j] = x;
                cout << " ";
            }
        }
    }
}

void tri_cocktail(vector<Element> &l) {
    bool echange = true;
    while (echange) {
        echange = false;
        
        for (int i = 0; i < l.size() - 2; i++) {
            if (l[i] > l[i+1]) {
                swap(l, i, i+1);
                echange = true;
            }
        }
        for (int i = l.size() - 2; i > 0; i--){
            if (l[i] > l[i+1]) {
                swap(l, i, i+1);
                echange = true;
            }
        }
    }
}

void tri_peigne(vector<Element> &l) {
    int intervalle = l.size();
    bool echange = false;

    while (intervalle > 1 || echange) {
        intervalle = int((double)intervalle / 1.3);
        if (intervalle < 1) intervalle = 1;
        
        int i = 0;
        echange = false;

        while (i < l.size() - intervalle) {
            if (l[i] > l[i+intervalle]) {
                swap(l, i, i+intervalle);
                echange = true;
            }
            i += 1;
            cout << " ";
        }
    }
}


void tri_pair_impair(vector<Element> &l) {
    bool trie = false;
    while (!trie) {
        trie = true;
        for (int x = 0; x < l.size() - 1; x += 2) {
            if (l[x] > l[x+1]){
                swap(l, x, x+1);
                trie = false;
            }
        }
        for (int x = 1; x < l.size() - 1; x += 2) {
            if (l[x] > l[x+1]){
                swap(l, x, x+1);
                trie = false;
            }
        }
    }
}

int partitionner(vector<Element> &l, int pivot) {
    swap(l, pivot, l.size()-1);
    int j = 0;
    for (int i = 0; i < l.size() - 1; i++) {
        if (l[i] <= l[l.size()-1]) {
            swap(l, i, j);
            j += 1;
        }
    }
    swap(l, j, l.size()-1);
    return j;
}

int partitionner_pointer(vector<Element*> &l, int pivot) {
    swap(l, pivot, l.size()-1);
    int j = 0;
    for (int i = 0; i < l.size() - 1; i++) {
        if (*l[i] <= *l[l.size()-1]) {
            swap(l, i, j);
            j += 1;
        }
    }
    swap(l, j, l.size()-1);
    return j;
}

int partitionner(vector<Element> &l, int premier, int dernier, int pivot) {
    swap(l, pivot, dernier);
    int j = premier;
    for (int i = premier; i < dernier; i++) {
        if (l[i] <= l[dernier]) {
            swap(l, i, j);
            j += 1;
        }
    cout << " ";
    }
    swap(l, dernier, j);
    return j;
}

void tri_rapide(vector<Element> &l, int premier, int dernier) {
    cout << " ";
    if (premier < dernier) {
        int pivot = (premier+dernier) / 2;
        pivot = partitionner(l, premier, dernier, pivot);
        tri_rapide(l, premier, pivot-1);
        tri_rapide(l, pivot+1, dernier);
    }
}

void launch_tri_rapide(vector<Element> &l) {
    tri_rapide(l, 0, l.size() - 1);
}

void tri_gnome(vector<Element> &l) {
    int pos = 0;
    while (pos < l.size()) {
        if (pos == 0 || l[pos] >= l[pos-1]) {
            pos += 1;
        } else {
            swap(l, pos, pos-1);
            pos -= 1;
        }
    }
}

void tri_oyelami(vector<Element> &l) {
    int n = l.size();
    bool sens = true; // true: avant, false: arriere
    int debut = 0, fin = n-2, en_cours = 1;
    
    for (int i = 1; i < n/2; i++) {
        if (l[i] > l[n-i]) swap(l, i, n-i);
    }
    bool permut = false;
    do {
        permut = false;
        do {
            if (l[en_cours] > l[en_cours + 1]) {
                swap(l, en_cours, en_cours+1);
                permut = true;
            }
            en_cours += sens ? 1 : -1;
        } while ((sens && en_cours < fin) || (!sens && en_cours > debut));
        if (sens) {
            fin -= 1;
        } else {
            debut += 1;
        }
        sens = !sens;
    } while (permut);
}

vector<Element*> fusion(vector<Element*> &a, vector<Element*> &b) {
    cout << a.size() << " " << b.size() << endl;
    if (a.size() == 0) {cout<<"a"<<endl;return b;}
    if (b.size() == 0) {cout<<"a"<<endl;return a;}
    if (a[0] <= b[0]) {
        Element& first = *a[0];
        vector<Element*> other = sublist(a, 1, a.size() - 1);
        fusion(other, b);
        insert(other, first);
        return other;
    } else {
        Element& first = *b[0];
        vector<Element*> other = sublist(b, 1, b.size() - 1);
        fusion(a, other);
        insert(other, first);
        return other;
    }
}

vector<Element*> tri_fusion_pointer(vector<Element*> &l) {
    cout << l.size() << endl;
    if (l.size() <= 2) return l;
    else {
        vector<Element*> le = sublist(l, 0, l.size()/2);
        vector<Element*> r = sublist(l, l.size()/2 + 1, l.size());
        vector<Element*> left = tri_fusion_pointer(le);
        vector<Element*> right = tri_fusion_pointer(r);
        vector<Element*> res = fusion(left, right);
        return res;
    }
    tick();
}

vector<Element*> tri_fusion_normal(vector<Element> &l) {
    if (l.size() <= 1) return vector<Element*>({&l[0]});
    else {
        vector<Element*> le = sublist(l, 0, l.size()/2);
        vector<Element*> r = sublist(l, l.size()/2 + 1, l.size() - 1);
        vector<Element*> left = tri_fusion_pointer(le);
        vector<Element*> right = tri_fusion_pointer(r);
        return fusion(left, right);
    }
}

void tri_fusion(vector<Element> &l) {
    tri_fusion_normal(l);
}


void flip(vector<Element> &l, int i) {
    int start = 0;
    while (start < i) {
        swap(l, start, i);
        start++;
        i--;
    }
}

int find_max(vector<Element> &l, int n) {
    int mi = 0;
    for (int i = 0; i < n; i++) {
        if (l[i] > l[mi]) {
            mi = i;
        }
    }
    return mi;
}

void tri_pancake(vector<Element> &l) {
    for (int curr_size = l.size(); curr_size > 1; curr_size--) {
        int mi = find_max(l, curr_size);
        if (mi != curr_size - 1) {
            flip(l, mi);
            flip(l, curr_size - 1);
        }
    }
}

void tri_bogo(vector<Element> &l) {
    bool tri = false;
    while (!tri) {
        random_shuffle(l.begin(), l.end());
        tri = true;
        for (int i = 0; i < l.size() - 2; i++) {
            if (l[i] > l[i+1]) {
                tri = false;
                break;
            }
        }
    }
}

void tri_bozo(vector<Element> &l) {
    bool tri = false;
    while (!tri) {
        swap(l, rand()%l.size(), rand()%l.size()),
        tri = true;
        for (int i = 0; i < l.size() - 2; i++) {
            if (l[i] > l[i+1]) {
                tri = false;
                break;
            }
        }
    }
}








void init() {
    functions.push_back(*tri_selection);
    names[*tri_selection] = wstring(L"Tri à sélection");
    functions.push_back(*tri_insertion);
    names[*tri_insertion] = wstring(L"Tri à insertion");
    functions.push_back(*tri_bulle);
    names[*tri_bulle] = wstring(L"Tri à bulle");
    functions.push_back(*tri_shell);
    names[*tri_shell] = wstring(L"Tri shell");
    functions.push_back(*tri_cocktail);
    names[*tri_cocktail] = wstring(L"Tri cocktail");
    functions.push_back(*tri_peigne);
    names[*tri_peigne] = wstring(L"Tri à peigne");
    functions.push_back(*tri_pair_impair);
    names[*tri_pair_impair] = wstring(L"Tri pair-impair");
    functions.push_back(*launch_tri_rapide);
    names[*launch_tri_rapide] = wstring(L"Tri rapide");
    functions.push_back(*tri_gnome);
    names[*tri_gnome] = wstring(L"Tri gnome");
    functions.push_back(*tri_oyelami);
    names[*tri_oyelami] = wstring(L"Tri oyelami / Cocktail optimisé");
    functions.push_back(*tri_fusion);
    names[*tri_fusion] = wstring(L"Tri fusion");
    functions.push_back(*tri_pancake);
    names[*tri_pancake] = wstring(L"Tri pancake");
    functions.push_back(*tri_bogo);
    names[*tri_bogo] = wstring(L"Tri bogo/stupide");
    functions.push_back(*tri_bozo);
    names[*tri_bozo] = wstring(L"Tri bozo");
}

wstring name(int i) {
    return names[functions[i]];
}

int sort_count() {
    return names.size();
}

void launch_function(int i, vector<Element> &l) {
    random_shuffle(l.begin(), l.end());
    functions[i](l);
}


