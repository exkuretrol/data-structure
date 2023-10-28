import streamlit as st
st.set_page_config(
    page_title="程式碼說明",
    page_icon="🤨",
)

st.header("程式碼說明")

hw_names = {"hw1": "作業一", "hw2": "作業二", "hw3": "作業三", "hw4": "作業四"}

hw = st.selectbox(label="作業", options=hw_names,
                  format_func=lambda x: hw_names.get(x))

if hw == "hw2":
    tab0, tab1, tab2, tab3, tab4 = st.tabs(
        ["main.cpp", "permutation.hpp", "tower-of-honai.hpp", "Permutation.py", "Tower_of_Honai.py"])

    with tab0:
        with open('src/main.cpp') as f:
            src = f.read()
        st.code(src, language="cpp")

    with tab1:
        with open('src/permutation.hpp') as f:
            src = f.read()
        st.code(src, language="cpp")

    with tab2:
        with open('src/tower-of-honai.hpp') as f:
            src = f.read()
        st.code(src, language="cpp")

    with tab3:
        with open('pages/1_🌧️_HW02_Permutation.py') as f:
            src = f.read()
        st.code(src)

    with tab4:
        with open('pages/2_🗼_HW02_Tower_of_Honai.py') as f:
            src = f.read()
        st.code(src)
elif hw == "hw3":
    tab0, tab1, tab2 = st.tabs(["main.cpp", "magic-square.hpp", "Magic_Square.py"])
    with tab0:
        with open('src/main.cpp') as f:
            src = f.read()
        st.code(src, language="cpp")
    
    with tab1:
        with open('src/magic-square.hpp') as f:
            src = f.read()
        st.code(src, language="cpp")

    with tab2:
        with open('pages/3_◾️_HW03_Magic_Square.py') as f:
            src = f.read()
        st.code(src)


else:
    st.write("還沒寫完")
