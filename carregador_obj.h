#ifndef CARREGADOR_OBJ_H
#define CARREGADOR_OBJ_H

#include <QString>
#include <memory>

#include "malha_obj.h"

class CarregadorOBJ {
public:
    /**
     * @brief Carrega um arquivo .obj e o converte em um objeto MalhaObj.
     * @param caminhoArquivo O caminho completo para o arquivo .obj.
     * @return Um shared_ptr para o objeto MalhaObj criado, ou nullptr em caso de erro.
     */
    static std::shared_ptr<MalhaObj> carregar(const QString& caminhoArquivo);
};

#endif // CARREGADOR_OBJ_H
