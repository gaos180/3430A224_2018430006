from typing import Any
from django.db.models import Q
from django.db.models.query import QuerySet
from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import login, authenticate, get_user_model
from django.contrib.auth.models import Group, User
from django.contrib.auth.forms import AuthenticationForm
from django.urls import reverse
from django.core.mail import send_mail
from django.http import JsonResponse, Http404
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from druggraph_admin.models import Drug, Target, InteractionDd, InteractionDt

from django.views.generic import TemplateView, ListView
"""
from .forms import RegistroDeUsuario
from .models import Denuncia
from .forms import UserRegisterForm
"""

def obteniendoDT(request):
    dts = InteractionDt.objects.all()
    dts_json = []
    for dt in dts:
        dt_interaction_data = {
            "drug_drug": dts.drug_drug,
            "target_target": dts.target_target,
            "type_interaction": dts.type_interaction,
        }
        dts_json.append(dt_interaction_data)
    return JsonResponse(dt_interaction_data, safe=False)


def index(request):
    return render(request, 'index.html')

class InteractionListView(ListView):
    model = InteractionDt
    template_name = 'interactions_list.html'
    context_object_name = 'interactions'

    def get_queryset(self):
        queryset = super().get_queryset().select_related('drug_drug', 'target_target')
        query = self.request.GET.get('q')
        search_type = self.request.GET.get('search_type')  # Obtener el tipo de búsqueda (exacta o parcial)

        if query:
            search_terms = [term.strip() for term in query.split(',') if term.strip()]
            query_filter = Q()

            for term in search_terms:
                if search_type == 'exact':
                    # Buscar coincidencias exactas para cada término
                    query_filter |= (
                        Q(drug_drug__name__iexact=term)
                        | Q(target_target__name__iexact=term)
                        | Q(type_interaction__iexact=term)
                    )
                else:
                    # Buscar coincidencias parciales si no se selecciona "exact"
                    query_filter |= (
                        Q(drug_drug__name__icontains=term)
                        | Q(target_target__name__icontains=term)
                        | Q(type_interaction__icontains=term)
                    )

            queryset = queryset.filter(query_filter)

        return queryset

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['query'] = self.request.GET.get('q', '')
        context['search_type'] = self.request.GET.get('search_type', 'contains')  # 'contains' es el valor por defecto
        context['total_interactions'] = self.get_queryset().count()
        return context


        
class SearchDrugListView(ListView):
    model = Drug
    template_name = "search.html"

