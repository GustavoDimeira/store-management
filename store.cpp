#include <iostream>
#include <vector>
#include <string>
#include <functional>
// #include <stdexcept>
#include <exception>
#include <conio.h>

using namespace std;

int client_code, product_code, option;

class Client {
  public: string name; int code; float debit;
    Client(string x) {
      code = client_code;
      name = x;
      debit = 0;

      client_code += 1;
    }
};

class Product {
  public: string name; int code; float price; int amount;
    Product(string x, float y, int z) {
      code = product_code;
      name = x;
      price = y;
      amount = z;

      product_code += 1;
    }
};

class Item {
  public: string name; int code; float price;
    Item(Product& x) {
      name = x.name;
      code = x.code;
      price = x.price;
    }
};

class Sell {
  public: string name_c; int code_c; vector<pair<Item, int>> purchases; int total = 0; string payment;
    Sell(Client& x, vector<pair<Item, int>>& y, string z) {
      name_c = x.name;
      code_c = x.code;
      purchases = y;
 
      for (int i = 0; i < y.size(); i++) {
        total += (y[i].first.price * y[i].second);
      };
 
      payment = z;
    }
};

class DB {
  public: vector<Client> clients; vector<Product> products; vector<Sell> sells;
};

int getProduct(DB& my_db) {
  int query_product;

  cout << "\n\nProdutos cadastrados: \n";
  for (int i = 0; i < my_db.products.size(); i++) {
    cout << "  -Nome: "<< my_db.products[i].name
           << "  -Código: " << my_db.products[i].code
           << "  -Quantia: " << my_db.products[i].amount
           << "  -Preço: " << my_db.products[i].price << " R$\n";
  };

  cout << "\n\nDigite o código do produto a ser modificado: ";
  cin >> query_product;

  return query_product;
};

Client getUser(DB& my_db) {
  int query_user;

  cout << "\n\nClientes cadastrados: \n";
  for (int i = 0; i < my_db.clients.size(); i++) {
    cout << "  -Nome: "<< my_db.clients[i].name << "  -Código: " << my_db.clients[i].code << "\n";
  };

  cout << "\nDigite o código do cliente: ";
  cin >> query_user;

  return my_db.clients[query_user];
};

vector<pair<Item, int>> getPurchases(DB& my_db) {
  string addMore = "S"; int amount; int query_product; vector<pair<Item, int>> purchases;
  
  while (addMore == "s" || addMore == "S") {
    try {
      cout << "\n\nProdutos cadastrados: \n";

      for (int i = 0; i < my_db.products.size(); i++) {
        cout << "  -Nome: "<< my_db.products[i].name
            << "  -Código: " << my_db.products[i].code
            << "  -Quantia: " << my_db.products[i].amount
            << "  -Preço: " << my_db.products[i].price << " R$\n";
      };

      cout << "\nCódigo do produto: ";
      cin >> query_product;

      cout << "\nQuantia do produto: ";
      cin >> amount;

      if (amount > my_db.products[query_product].amount) {
        cout << "\n\nQuantia de produtos no estoque é insuficiente, produto não adicionado";
      } else {
          my_db.products[query_product].amount -= amount;
          cout << "\n\nProduto adicionado com sucesso";

          Item newItem(my_db.products[query_product]);
          purchases.push_back( { newItem, amount } );
      };

      cout << "\nPara adicionar mais produtos, digite S: ";
      cin >> addMore;
    } catch (exception& e) {
      cout << "Valor incorreto, ou produto não encontrado";
    }
  };
  return purchases;
};

void chose_option_msg() {
  cout << "Escolha uma opção: \n";
  cout << " - 1 Cadastrar novo cliente" << "\n";
  cout << " - 2 Cadastrar novo produto" << "\n";
  cout << " - 3 Cadastrar nova venda" << "\n";
  cout << " - 4 Buscar cliente por código" << "\n";
  cout << " - 5 Atualizar Produto existente" << "\n";
  cout << " - 6 Mostrar relatorio" << "\n";
  cout << " - 7 Sair" << "\n\n";
  cout << "Opção: ";

  cin >> option;

  if (option < 0 || option > 7) { throw out_of_range(); };
};

void createUser(DB& my_db) {
  string name;

  cout << "\n\nInsira o nome do novo usuário: ";
  cin >> name;

  Client newUser(name);
  my_db.clients.push_back(newUser);
};

void createProduct(DB& my_db) {
  string name; float price; int amount;

  cout << "\n\nDigite um nome para o produto: ";
  cin >> name;

  cout << "\n\nDigite o preço (maior que 0): ";
  cin >> price;

  if (price <= 0) { throw out_of_range(); };

  cout << "\n\nDigite a quantia de itens presente no estoque: ";
  cin >> amount;

  Product newProduct(name, price, amount);
  my_db.products.push_back(newProduct);
};

void createSell(DB& my_db) {
  Client buyer = getUser(my_db); vector<pair<Item, int>> purchases = getPurchases(my_db);
  
  string payment;
  cout << "\n\nQual seria a forma de pagamento: ";
  cin >> payment;

  Sell newSell(buyer, purchases, payment);
  my_db.sells.push_back(newSell);
};

void findClient(DB& my_db) {
  Client user = getUser(my_db);
  cout << "\n\n-Nome: "<< user.name << "  -Código: " << user.code << "\n";
}

void updateProduct(DB& my_db) {
  int query_product = getProduct(my_db); int toChange; int amount; float price; string name;
  vector<string> variables = { "name", "price", "amount" };

  cout << "\n\n-1 Nome";
  cout << "\n-2 Preço";
  cout << "\n-3 Quantia";
  cout << "\n\nQual variavel sera modificada: ";

  cin >> toChange;

  cout << "\n\nDigite o novo valor: ";

  if (toChange == 1) {
    cin >> name;
    my_db.products[query_product].name = name;
  } else if (toChange == 2) {
    cin >> price;
    my_db.products[query_product].price = price;
  } else {
    cin >> amount;
    my_db.products[query_product].amount = amount;
  }
};

void getReport(DB& my_db) {
  
};

vector<function<void(DB&)>> flow;

int main() {
  DB my_db;

  flow.push_back(createUser);
  flow.push_back(createProduct);
  flow.push_back(createSell);
  flow.push_back(findClient);
  flow.push_back(updateProduct);
  flow.push_back(getReport);

  while(option != 7) {
    try {
      chose_option_msg();
      flow[option - 1](my_db);
    } catch(exception& e) {
      cout << "Algum valor foi digitado incorretamente, tente novamente.";
      option = 0;
    };
  };

  return 0;
};
