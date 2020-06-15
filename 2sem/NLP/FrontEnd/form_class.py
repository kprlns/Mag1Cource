from wtforms import Form, StringField, SelectField, SubmitField, BooleanField
from wtforms import IntegerField
import wtforms


class SearchForm(Form):
    search_query = StringField('Запрос')
    num_of_result = IntegerField('Количество результатов')
    only_headers = BooleanField('Показывать только заголовки')
    submit = SubmitField('Искать')
