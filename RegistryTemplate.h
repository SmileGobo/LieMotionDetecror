#ifndef REGISTRYSINGLETONETEMPLATE_H
#define REGISTRYSINGLETONETEMPLATE_H
#include <QHash>
template <class T> class Registry{
    public:
        ~Registry();
        void RegElem(T* reg_data,const QString& key){
            m_reg_data.insert(key,reg_data);
            //m_reg_data[key]=reg_data;
        }

        T* GetElem(const QString &reg_key){
            return m_reg_data.value(reg_key,NULL);
        };

        static Registry* GetInstance(){
            if (m_instance==0){
                m_instance=new Registry();
            }
            return m_instance;
        }

    private:
        Registry(){};
        static Registry *m_instance;
        QHash<QString,T*> m_reg_data;
};
template<class T>
    Registry <T>  *Registry<T>::m_instance = 0;

#endif // REGISTRYSINGLETONETEMPLATE_H
